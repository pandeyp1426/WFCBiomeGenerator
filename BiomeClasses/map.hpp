#pragma once

#include <cstdint>
#include <random>
#include <tuple>
#include <vector>

#include "cell.hpp"
#include "BiomeDFA.hpp"

class Map
{
private:
    using BiomeRule = BiomeDFA::BiomeRule;

    int numRows = 0;
    int numCols = 0;
    std::vector<Cell> cells;
    std::vector<BiomeRule> biomeRules;
    std::mt19937 rng;
    std::uint32_t seed = 0;

    void initializeCells();
    void buildRules();
    int indexOf(int row, int col) const;

public:
    Map(int numOfRows, int numOfCols, std::uint32_t seed = 1337u);

    int getNumRows() const;
    int getNumCols() const;
    std::uint32_t getSeed() const;

    bool isInBounds(int row, int col) const;

    Cell& getCell(int rowNum, int colNum);
    const Cell& getCell(int rowNum, int colNum) const;

    const std::vector<BiomeRule>& getBiomeRules() const { return biomeRules; }

    void paintCell(int rowNum, int colNum, Biome biome);
    void resetToUncollapsed();
};