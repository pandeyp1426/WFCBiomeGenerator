#pragma once
#include <SFML/Graphics.hpp>

inline sf::Color biomeToColor(char biome)
{
    switch (biome)
    {
        case 'C':  return sf::Color(240, 230, 140); // Coast
        case 'D':  return sf::Color(181, 66, 51);   // Desert
        case 'F':  return sf::Color(34, 139, 34);   // Forest
        case 'I':  return sf::Color(16, 38, 17);    // Deep Forest
        case 'M':  return sf::Color(128, 128, 128); // Mountains
        case 'O':  return sf::Color(0, 105, 148);   // Ocean
        case 'P':  return sf::Color(66, 26, 4);   // Plains
        case 'S':  return sf::Color(30, 32, 117);   // Deep Ocean
        default:        return sf::Color::White;
    }
}