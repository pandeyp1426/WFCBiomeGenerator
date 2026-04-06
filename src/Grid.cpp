#include "Grid.hpp"

Grid::Grid(int rows, int cols)
    : m_rows(rows), m_cols(cols), m_cells(rows, std::vector<Biome>(cols, Biome::Plains))
{
    loadSampleMap();
}

int Grid::getRows() const
{
    return m_rows;
}

int Grid::getCols() const
{
    return m_cols;
}

Biome Grid::getCell(int row, int col) const
{
    return m_cells[row][col];
}

void Grid::setCell(int row, int col, Biome biome)
{
    m_cells[row][col] = biome;
}

void Grid::reset()
{
    loadSampleMap();
}

void Grid::loadSampleMap()
{
    for (int r = 0; r < m_rows; ++r)
    {
        for (int c = 0; c < m_cols; ++c)
        {
            if (c < 3)
            {
                m_cells[r][c] = Biome::Ocean;
            }
            else if (c < 5)
            {
                m_cells[r][c] = Biome::Coast;
            }
            else if (c < 12)
            {
                m_cells[r][c] = Biome::Plains;
            }
            else if (c < 16)
            {
                m_cells[r][c] = Biome::Forest;
            }
            else
            {
                m_cells[r][c] = Biome::Mountains;
            }
        }
    }

    for (int r = 10; r < 15 && r < m_rows; ++r)
    {
        for (int c = 8; c < 12 && c < m_cols; ++c)
        {
            m_cells[r][c] = Biome::Swamp;
        }
    }
}