#pragma once

#include <SFML/Graphics.hpp>
#include "../BiomeClasses/map.hpp"

class Renderer
{
private:
    float tileSize = 1.0f;
    sf::RectangleShape tileShape;

public:
    explicit Renderer(float tileSize);

    void draw(sf::RenderTarget& target, const Map& map) const;
    static sf::Color colorForBiome(Biome biome);
};