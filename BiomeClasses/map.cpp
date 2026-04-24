#include "map.hpp"

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

Map::Map(int numOfRows, int numOfCols, std::uint32_t inputSeed)
    : numRows(numOfRows), numCols(numOfCols), rng(inputSeed), seed(inputSeed)
{
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

    biomeRules[static_cast<int>(Biome::Ocean)].allowedNeighbors = makeMask({ Biome::Ocean, Biome::Coast });
    biomeRules[static_cast<int>(Biome::Coast)].allowedNeighbors = makeMask({ Biome::Ocean, Biome::Coast, Biome::Beach, Biome::Plains });
    biomeRules[static_cast<int>(Biome::Beach)].allowedNeighbors = makeMask({ Biome::Coast, Biome::Beach, Biome::Plains, Biome::Desert });
	biomeRules[static_cast<int>(Biome::Plains)].allowedNeighbors = makeMask({ Biome::Coast, Biome::Beach, Biome::Plains, Biome::Forest, Biome::Desert });
    biomeRules[static_cast<int>(Biome::Forest)].allowedNeighbors = makeMask({ Biome::Plains, Biome::Forest, Biome::Mountain}); 
    biomeRules[static_cast<int>(Biome::Desert)].allowedNeighbors = makeMask({ Biome::Beach, Biome::Plains, Biome::Desert, Biome::Mountain });
    biomeRules[static_cast<int>(Biome::Mountain)].allowedNeighbors = makeMask({ Biome::Plains, Biome::Forest, Biome::Desert, Biome::Mountain});
}
void Map::resetToUncollapsed()
{
    for (Cell& cell : cells)
        cell.reset(fullBiomeMask());
}

void Map::paintCell(int rowNum, int colNum, Biome biome)
{
    if (!isInBounds(rowNum, colNum))
        return;
    getCell(rowNum, colNum).collapseTo(biome);
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
std::uint32_t Map::getSeed() const { return seed; }

Cell& Map::getCell(int rowNum, int colNum)
{
    return cells.at(static_cast<std::size_t>(indexOf(rowNum, colNum)));
}

const Cell& Map::getCell(int rowNum, int colNum) const
{
    return cells.at(static_cast<std::size_t>(indexOf(rowNum, colNum)));
}