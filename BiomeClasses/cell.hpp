#pragma once

#include <cstdint>

enum class Biome : std::uint8_t
{
    Ocean = 0,
    Coast,
    Beach,
    Plains,
    Forest,
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
    bool locked = false;
    bool collapsed = false;
    Biome collapsedBiome = Biome::Ocean;
    std::uint16_t possibleMask = 0;
    float cachedEntropy = 0.0f;

public:
    Cell() = default;
    Cell(int cellRow, int cellCol);

    void reset(std::uint16_t fullMask);
    void lockTo(Biome biome);
    void collapseTo(Biome biome);

    bool isLocked() const;
    bool isCollapsed() const;
    int getRow() const;
    int getCol() const;
    Biome getBiome() const;
    std::uint16_t getPossibleMask() const;
    void setPossibleMask(std::uint16_t newMask);
    bool hasOption(Biome biome) const;
    int getNumberOfRemainingOptions() const;

    void setCellEntropy(float entropy);
    float getCellEntropy() const;

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
char biomeToSymbol(Biome biome);
Biome biomeFromSymbol(char symbol);
const char* biomeName(Biome biome);
