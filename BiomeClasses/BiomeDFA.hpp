#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

class BiomeDFA
{
public:
    struct BiomeRule
    {
        char biome = '\0';
        std::uint16_t allowedNeighbors = 0;
    };

    static bool transition(char currentState, char input,
        const std::vector<BiomeRule>& rules)
    {
        const BiomeRule* rule = findRule(currentState, rules);
        if (rule == nullptr)
        {
            return false;
        }

        return (rule->allowedNeighbors & biomeMask(input)) != 0;
    }

    static std::uint16_t allowedNeighborMask(std::uint16_t sourceMask,
        const std::vector<BiomeRule>& rules)
    {
        std::uint16_t allowed = 0;
        for (const BiomeRule& rule : rules)
        {
            if ((sourceMask & biomeMask(rule.biome)) == 0)
            {
                continue;
            }

            allowed = static_cast<std::uint16_t>(
                allowed | rule.allowedNeighbors);
        }

        return allowed;
    }

    static bool accepts(const std::vector<char>& sequence,
        const std::vector<BiomeRule>& rules)
    {
        for (std::size_t i = 1; i < sequence.size(); ++i)
        {
            if (!transition(sequence[i - 1], sequence[i], rules))
            {
                return false;
            }
        }

        return true;
    }

    static constexpr int biomeCount()
    {
        return static_cast<int>(allBiomes.size());
    }

    static constexpr std::uint16_t biomeMask(char biome)
    {
        switch (biome)
        {
        case 'C':
            return static_cast<std::uint16_t>(1u << 0);
        case 'D':
            return static_cast<std::uint16_t>(1u << 1);
        case 'F':
            return static_cast<std::uint16_t>(1u << 2);
        case 'M':
            return static_cast<std::uint16_t>(1u << 3);
        case 'O':
            return static_cast<std::uint16_t>(1u << 4);
        case 'P':
            return static_cast<std::uint16_t>(1u << 5);
        case 'I':
            return static_cast<std::uint16_t>(1u << 6);
        case 'S':
            return static_cast<std::uint16_t>(1u << 7);
        default:
            return 0;
        }
    }

private:
    inline static constexpr std::array<char, 8> allBiomes = {
        'C', 'D', 'F', 'M', 'O', 'P', 'I', 'S'
    };

    static const BiomeRule* findRule(char biome,
        const std::vector<BiomeRule>& rules)
    {
        for (const BiomeRule& rule : rules)
        {
            if (rule.biome == biome)
            {
                return &rule;
            }
        }

        return nullptr;
    }
};
