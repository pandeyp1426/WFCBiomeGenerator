#pragma once

#include "cell.hpp"
#include <vector>

class BiomeDFA
{
public:
    struct BiomeRule
    {
        std::uint16_t allowedNeighbors = 0;
    };

    // δ(state, input) — is this neighbor transition valid?
    static bool transition(Biome currentState, Biome input,
        const std::vector<BiomeRule>& rules)
    {
        const int index = static_cast<int>(currentState);
        if (index < 0 || index >= static_cast<int>(rules.size()))
            return false;
        return (rules[static_cast<std::size_t>(index)].allowedNeighbors
            & biomeMask(input)) != 0;
    }

    // Returns bitmask of all biomes allowed next to any biome in sourceMask
    static std::uint16_t allowedNeighborMask(std::uint16_t sourceMask,
        const std::vector<BiomeRule>& rules)
    {
        std::uint16_t allowed = 0;
        for (int i = 0; i < biomeCount(); ++i)
        {
            if ((sourceMask & (1u << i)) == 0)
                continue;
            allowed = static_cast<std::uint16_t>(
                allowed | rules[static_cast<std::size_t>(i)].allowedNeighbors);
        }
        return allowed;
    }

    // Accepts a linear sequence — true if every adjacent pair is valid
    static bool accepts(const std::vector<Biome>& sequence,
        const std::vector<BiomeRule>& rules)
    {
        for (std::size_t i = 1; i < sequence.size(); ++i)
            if (!transition(sequence[i - 1], sequence[i], rules))
                return false;
        return true;
    }
};