#pragma once
#include <SFML/Graphics.hpp>

enum class Biome
{
    Ocean,
    Coast,
    Plains,
    Forest,
    Swamp,
    Mountains
};

inline sf::Color biomeToColor(Biome biome)
{
    switch (biome)
    {
    case Biome::Ocean:     return sf::Color(0, 105, 148);
    case Biome::Coast:     return sf::Color(240, 230, 140);
    case Biome::Plains:    return sf::Color(50, 205, 50);
   // case Biome::Forest:    return sf::Color(34, 139, 34);
   // case Biome::Swamp:     return sf::Color(47, 79, 79);
   // case Biome::Mountains: return sf::Color(128, 128, 128);
    default:               return sf::Color::White;
    }
}