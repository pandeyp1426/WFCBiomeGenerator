#include "map.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace
{
    std::uint16_t makeMask(std::initializer_list<Biome> biomes)
    {
        std::uint16_t mask = 0;
        for (const Biome biome : biomes)
            mask = static_cast<std::uint16_t>(mask | biomeMask(biome));
        return mask;
    }
} // namespace

Map::Map(int numOfRows, int numOfCols)
    : numRows(numOfRows), numCols(numOfCols)
{
    std::random_device rd;
    rng.seed(rd());
    initializeCells();
    buildRules();
}

void Map::initializeCells()
{
    cells.clear();
    cells.reserve(static_cast<std::size_t>(numRows * numCols));
    for (int row = 0; row < numRows; ++row)
        for (int col = 0; col < numCols; ++col)
            cells.emplace_back(row, col);
}

void Map::buildRules()
{
    biomeRules.assign(static_cast<std::size_t>(biomeCount()), {});

    biomeRules[static_cast<int>(Biome::DeepOcean)].allowedNeighbors = makeMask({ Biome::DeepOcean, Biome::Ocean });
    biomeRules[static_cast<int>(Biome::Ocean)].allowedNeighbors = makeMask({ Biome::DeepOcean, Biome::Ocean, Biome::Coast });
    biomeRules[static_cast<int>(Biome::Coast)].allowedNeighbors = makeMask({ Biome::Ocean, Biome::Coast, Biome::Beach, Biome::Plains });
    biomeRules[static_cast<int>(Biome::Beach)].allowedNeighbors = makeMask({ Biome::Coast, Biome::Beach, Biome::Plains, Biome::Desert });
    biomeRules[static_cast<int>(Biome::Plains)].allowedNeighbors = makeMask({ Biome::Coast, Biome::Beach, Biome::Plains, Biome::Forest, Biome::Desert, Biome::Mountain });
    biomeRules[static_cast<int>(Biome::Forest)].allowedNeighbors = makeMask({ Biome::Plains, Biome::Forest, Biome::DeepForest, Biome::Mountain });
    biomeRules[static_cast<int>(Biome::DeepForest)].allowedNeighbors = makeMask({ Biome::Forest, Biome::DeepForest });
    biomeRules[static_cast<int>(Biome::Desert)].allowedNeighbors = makeMask({ Biome::Beach, Biome::Plains, Biome::Desert, Biome::Mountain });
    biomeRules[static_cast<int>(Biome::Mountain)].allowedNeighbors = makeMask({ Biome::Plains, Biome::Forest, Biome::Desert, Biome::Mountain, Biome::Snow });
    biomeRules[static_cast<int>(Biome::Snow)].allowedNeighbors = makeMask({ Biome::Mountain, Biome::Snow });
}

void Map::resetToUncollapsed()
{
    for (Cell& cell : cells)
        cell.reset(fullBiomeMask());
}

void Map::resetEntropyQueue()
{
    EntropyQueue empty;
    std::swap(entropyQueue, empty);
}

void Map::pushEntropy(int cellIndex, float entropy)
{
    entropyQueue.push({ entropy, cellIndex });
}

void Map::startGeneration()
{
    rng.seed(std::random_device{}());
    resetToUncollapsed();
    resetEntropyQueue();

    for (int index = 0; index < static_cast<int>(cells.size()); ++index)
    {
        Cell& cell = cells[static_cast<std::size_t>(index)];
        const float entropy = computeEntropy(cell);
        cell.setCellEntropy(entropy);
        pushEntropy(index, entropy);
    }
}

bool Map::generateStep()
{
    const int nextCellIndex = findLowestEntropyCell();
    if (nextCellIndex < 0)
        return false;

    Cell& cell = cells[static_cast<std::size_t>(nextCellIndex)];
    cell.collapseTo(chooseRandomBiome(cell));

    std::queue<int> propagationQueue;
    propagationQueue.push(nextCellIndex);
    propagate(propagationQueue);

    return true;
}

bool Map::tryCollapseMap()
{
    resetEntropyQueue();

    for (int index = 0; index < static_cast<int>(cells.size()); ++index)
    {
        Cell& cell = cells[static_cast<std::size_t>(index)];
        if (cell.getNumberOfRemainingOptions() == 0)
            return false;

        const float entropy = computeEntropy(cell);
        cell.setCellEntropy(entropy);
        pushEntropy(index, entropy);
    }

    while (true)
    {
        const int nextCellIndex = findLowestEntropyCell();
        if (nextCellIndex < 0)
            return true;

        Cell& cell = cells[static_cast<std::size_t>(nextCellIndex)];
        cell.collapseTo(chooseRandomBiome(cell));

        std::queue<int> propagationQueue;
        propagationQueue.push(nextCellIndex);
        if (!propagate(propagationQueue))
            return false;
    }
}

bool Map::propagate(std::queue<int>& pendingCells)
{
    static constexpr int rowOffsets[4] = { -1, 0, 1, 0 };
    static constexpr int colOffsets[4] = { 0, 1, 0, -1 };

    while (!pendingCells.empty())
    {
        const int sourceIndex = pendingCells.front();
        pendingCells.pop();

        const Cell& sourceCell = cells[static_cast<std::size_t>(sourceIndex)];
        const int row = sourceCell.getRow();
        const int col = sourceCell.getCol();

        for (int direction = 0; direction < 4; ++direction)
        {
            const int nextRow = row + rowOffsets[direction];
            const int nextCol = col + colOffsets[direction];
            if (!isInBounds(nextRow, nextCol))
                continue;

            const int neighborIndex = indexOf(nextRow, nextCol);
            if (reduceNeighborOptions(sourceIndex, neighborIndex))
                pendingCells.push(neighborIndex);

            if (cells[static_cast<std::size_t>(neighborIndex)].getNumberOfRemainingOptions() == 0)
                return false;
        }
    }

    return true;
}

bool Map::reduceNeighborOptions(int sourceIndex, int neighborIndex)
{
    const Cell& sourceCell = cells[static_cast<std::size_t>(sourceIndex)];
    Cell& neighborCell = cells[static_cast<std::size_t>(neighborIndex)];

    const std::uint16_t allowedMask =
        BiomeDFA::allowedNeighborMask(sourceCell.getPossibleMask(), biomeRules);

    const std::uint16_t oldMask = neighborCell.getPossibleMask();
    const std::uint16_t newMask = static_cast<std::uint16_t>(oldMask & allowedMask);

    if (newMask == oldMask)
        return false;

    neighborCell.setPossibleMask(newMask);

    if (newMask != 0)
    {
        const float entropy = computeEntropy(neighborCell);
        neighborCell.setCellEntropy(entropy);
        pushEntropy(neighborIndex, entropy);
    }

    return true;
}

int Map::findLowestEntropyCell()
{
    while (!entropyQueue.empty())
    {
        auto [entropy, index] = entropyQueue.top();
        entropyQueue.pop();

        const Cell& cell = cells[static_cast<std::size_t>(index)];

        if (cell.isCollapsed())
            continue;
        if (std::abs(cell.getCellEntropy() - entropy) > 0.0001f)
            continue;

        return index;
    }

    return -1;
}

float Map::computeEntropy(const Cell& cell) const
{
    if (cell.isCollapsed())
        return 0.0f;
    return static_cast<float>(cell.getNumberOfRemainingOptions());
}

Biome Map::chooseRandomBiome(const Cell& cell)
{
    std::vector<Biome> options;
    for (int i = 0; i < biomeCount(); ++i)
    {
        const Biome biome = static_cast<Biome>(i);
        if (cell.hasOption(biome))
            options.push_back(biome);
    }

    if (options.empty())
        return Biome::Ocean;

    std::uniform_int_distribution<int> dist(0, static_cast<int>(options.size()) - 1);
    return options[static_cast<std::size_t>(dist(rng))];
}

void Map::generate(int maxAttempts)
{
    for (int attempt = 0; attempt < maxAttempts; ++attempt)
    {
        generationAttempts = attempt + 1;
        rng.seed(std::random_device{}());
        resetToUncollapsed();

        if (tryCollapseMap())
            return;
    }
}

int Map::indexOf(int row, int col) const
{
    return row * numCols + col;
}

bool Map::isInBounds(int row, int col) const
{
    return row >= 0 && row < numRows && col >= 0 && col < numCols;
}

int Map::getNumRows() const { return numRows; }
int Map::getNumCols() const { return numCols; }
int Map::getGenerationAttempts() const { return generationAttempts; }

Cell& Map::getCell(int rowNum, int colNum)
{
    return cells.at(static_cast<std::size_t>(indexOf(rowNum, colNum)));
}

const Cell& Map::getCell(int rowNum, int colNum) const
{
    return cells.at(static_cast<std::size_t>(indexOf(rowNum, colNum)));
}
