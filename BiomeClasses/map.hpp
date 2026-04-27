#pragma once

#include <cstdint>
#include <functional>
#include <queue>
#include <random>
#include <utility>
#include <vector>

#include "cell.hpp"
#include "BiomeDFA.hpp"

class Map
{
private:
    using BiomeRule = BiomeDFA::BiomeRule;

    using EntropyQueue = std::priority_queue<
        std::pair<float, int>,
        std::vector<std::pair<float, int>>,
        std::greater<std::pair<float, int>> > ;

    int numRows = 0;
    int numCols = 0;
    std::vector<Cell> cells;
    std::vector<BiomeRule> biomeRules;
    EntropyQueue entropyQueue;
    std::mt19937 rng;
    std::uint32_t currentSeed = 0;
    int generationAttempts = 0;

    void initializeCells();
    void buildRules();
    void resetToUncollapsed();
    void resetEntropyQueue();
    void pushEntropy(int cellIndex, float entropy);

    bool tryCollapseMap();
    bool propagate(std::queue<int>& pendingCells);
    bool reduceNeighborOptions(int sourceIndex, int neighborIndex);
    int findLowestEntropyCell();
    float computeEntropy(const Cell& cell) const;
    Biome chooseRandomBiome(const Cell& cell);

    int indexOf(int row, int col) const;

public:
    Map(int numOfRows, int numOfCols);

    int getNumRows() const;
    int getNumCols() const;
    int getGenerationAttempts() const;
    std::uint32_t getSeed() const;
    bool isInBounds(int row, int col) const;

    Cell& getCell(int rowNum, int colNum);
    const Cell& getCell(int rowNum, int colNum) const;

    void generate(int maxAttempts = 32);
    void startGeneration();
    void startGeneration(std::uint32_t seed);
    bool generateStep();
};
