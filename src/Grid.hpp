#pragma once
#include <vector>
#include "Biome.hpp"

class Grid
{
public:
    Grid(int rows, int cols);

    int getRows() const;
    int getCols() const;

    Biome getCell(int row, int col) const;
    void setCell(int row, int col, Biome biome);

    void loadSampleMap();
    void reset();

private:
    int m_rows;
    int m_cols;
    std::vector<std::vector<Biome>> m_cells;
};