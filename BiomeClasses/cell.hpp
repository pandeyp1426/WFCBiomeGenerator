#pragma once

#include <cstdint>

enum class Biome : std::uint8_t
{
    DeepOcean = 0,
    Ocean,
    Coast,
    Beach,
    Plains,
    Forest,
    DeepForest,
    Desert,
    Mountain,
    Snow,
    Count
};

class Cell
{
private:
    int cellRow = 0;
    int cellCol = 0;
    bool collapsed = false;
    Biome collapsedBiome = Biome::Ocean;
    std::uint16_t possibleMask = 0;
    float cachedEntropy = 0.0f;

public:
    Cell() = default;
    Cell(int cellRow, int cellCol);

    void reset(std::uint16_t fullMask);
    void collapseTo(Biome biome);

    void setPossibleMask(std::uint16_t newMask);
    bool hasOption(Biome biome) const;
    int getNumberOfRemainingOptions() const { return countBits(possibleMask); }

    void setCellEntropy(float entropy);
    float getCellEntropy() const { return cachedEntropy; }

    bool  isCollapsed() const { return collapsed; }
    int   getRow() const { return cellRow; }
    int   getCol() const { return cellCol; }
    Biome getBiome() const { return collapsedBiome; }
    std::uint16_t getPossibleMask() const { return possibleMask; }
};

constexpr int biomeCount()
{
    return static_cast<int>(Biome::Count);
}

constexpr std::uint16_t fullBiomeMask()
{
    return static_cast<std::uint16_t>((1u << biomeCount()) - 1u);
}

std::uint16_t biomeMask(Biome biome);