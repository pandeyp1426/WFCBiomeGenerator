#include "cell.hpp"

namespace
{
    int countBits(std::uint16_t mask)
    {
        int count = 0;
        while (mask != 0)
        {
            count += static_cast<int>(mask & 1u);
            mask >>= 1u;
        }
        return count;
    }

    Biome biomeFromSingleMask(std::uint16_t mask)
    {
        for (int index = 0; index < biomeCount(); ++index)
        {
            if (mask == static_cast<std::uint16_t>(1u << index))
                return static_cast<Biome>(index);
        }
        return Biome::Ocean;
    }
} // namespace

Cell::Cell(int inCellRow, int inCellCol) : cellRow(inCellRow), cellCol(inCellCol)
{
    reset(fullBiomeMask());
}

void Cell::reset(std::uint16_t fullMask)
{
    collapsed = false;
    collapsedBiome = Biome::Ocean;
    possibleMask = fullMask;
    cachedEntropy = 0.0f;
}

void Cell::collapseTo(Biome biome)
{
    collapsed = true;
    collapsedBiome = biome;
    possibleMask = biomeMask(biome);
    cachedEntropy = 0.0f;
}

void Cell::setPossibleMask(std::uint16_t newMask)
{
    possibleMask = newMask;
    const int remaining = countBits(possibleMask);
    collapsed = (remaining == 1);
    if (collapsed)
        collapsedBiome = biomeFromSingleMask(possibleMask);
}

bool Cell::hasOption(Biome biome) const
{
    return (possibleMask & biomeMask(biome)) != 0;
}

void  Cell::setCellEntropy(float entropy) { cachedEntropy = entropy; }

std::uint16_t biomeMask(Biome biome)
{
    return static_cast<std::uint16_t>(1u << static_cast<int>(biome));
}