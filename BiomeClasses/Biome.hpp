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

inline sf::Color biomeToColor(char biome)
{
    switch (biome)
    {
        case 'C':  return sf::Color(240, 230, 140);
        case 'D':  return sf::Color(204, 173, 96);
        case 'F':  return sf::Color(34, 139, 34);
        case 'M':  return sf::Color(128, 128, 128);
        case 'O':  return sf::Color(0, 105, 148);
        case 'P':  return sf::Color(50, 205, 50);
        default:        return sf::Color::White;
    }
}