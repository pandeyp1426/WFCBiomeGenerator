#include "cell.hpp"

#include <cctype>

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
            {
                return static_cast<Biome>(index);
            }
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
    locked = false;
    collapsed = false;
    collapsedBiome = Biome::Ocean;
    possibleMask = fullMask;
    cachedEntropy = 0.0f;
}

void Cell::lockTo(Biome biome)
{
    locked = true;
    collapseTo(biome);
}

void Cell::collapseTo(Biome biome)
{
    collapsed = true;
    collapsedBiome = biome;
    possibleMask = biomeMask(biome);
    cachedEntropy = 0.0f;
}

bool Cell::isLocked() const
{
    return locked;
}

bool Cell::isCollapsed() const
{
    return collapsed;
}

int Cell::getRow() const
{
    return cellRow;
}

int Cell::getCol() const
{
    return cellCol;
}

Biome Cell::getBiome() const
{
    return collapsedBiome;
}

std::uint16_t Cell::getPossibleMask() const
{
    return possibleMask;
}

void Cell::setPossibleMask(std::uint16_t newMask)
{
    possibleMask = newMask;

    const int remainingOptions = countBits(possibleMask);
    collapsed = (remainingOptions == 1);
    if (collapsed)
    {
        collapsedBiome = biomeFromSingleMask(possibleMask);
    }
}

bool Cell::hasOption(Biome biome) const
{
    return (possibleMask & biomeMask(biome)) != 0;
}

int Cell::getNumberOfRemainingOptions() const
{
    return countBits(possibleMask);
}

void Cell::setCellEntropy(float entropy)
{
    cachedEntropy = entropy;
}

float Cell::getCellEntropy() const
{
    return cachedEntropy;
}

std::uint16_t biomeMask(Biome biome)
{
    return static_cast<std::uint16_t>(1u << static_cast<int>(biome));
}

char biomeToSymbol(Biome biome)
{
    switch (biome)
    {
    case Biome::Ocean:
        return 'O';
    case Biome::Coast:
        return 'C';
    case Biome::Beach:
        return 'B';
    case Biome::Plains:
        return 'P';
    case Biome::Forest:
        return 'F';
    case Biome::Desert:
        return 'D';
    case Biome::Mountain:
        return 'M';
    case Biome::Snow:
        return 'S';
    case Biome::Count:
        break;
    }

    return '?';
}

Biome biomeFromSymbol(char symbol)
{
    switch (static_cast<char>(std::toupper(static_cast<unsigned char>(symbol))))
    {
    case 'O':
        return Biome::Ocean;
    case 'C':
        return Biome::Coast;
    case 'B':
        return Biome::Beach;
    case 'P':
        return Biome::Plains;
    case 'F':
        return Biome::Forest;
    case 'D':
        return Biome::Desert;
    case 'M':
        return Biome::Mountain;
    case 'S':
        return Biome::Snow;
    default:
        return Biome::Plains;
    }
}

const char* biomeName(Biome biome)
{
    switch (biome)
    {
    case Biome::Ocean:
        return "Ocean";
    case Biome::Coast:
        return "Coast";
    case Biome::Beach:
        return "Beach";
    case Biome::Plains:
        return "Plains";
    case Biome::Forest:
        return "Forest";
    case Biome::Desert:
        return "Desert";
    case Biome::Mountain:
        return "Mountain";
    case Biome::Snow:
        return "Snow";
    case Biome::Count:
        break;
    }

    return "Unknown";
}
