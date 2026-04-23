#pragma once
#include <SFML/Graphics.hpp>

enum class Biome
{
    C, // Coast
    D, // Desert
    F, // Forest
    M, // Mountains
    O, // Ocean
    P, // Plains
};

inline sf::Color biomeToColor(Biome biome)
{
    switch (biome)
    {
        case Biome::C:  return sf::Color(240, 230, 140);
        case Biome::D:  return sf::Color(204, 173, 96);
        case Biome::F:  return sf::Color(34, 139, 34);
        case Biome::M:  return sf::Color(128, 128, 128);
        case Biome::O:  return sf::Color(0, 105, 148);
        case Biome::P:  return sf::Color(50, 205, 50);
        default:        return sf::Color::White;
    }
}