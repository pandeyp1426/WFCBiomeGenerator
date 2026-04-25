#include "mapRenderer.hpp"

Renderer::Renderer(float inTileSize)
    : tileSize(inTileSize), tileShape(sf::Vector2f(inTileSize, inTileSize))
{
}

void Renderer::draw(sf::RenderTarget& target, const Map& map) const
{
    sf::RectangleShape tile = tileShape;

    for (int row = 0; row < map.getNumRows(); ++row)
    {
        for (int col = 0; col < map.getNumCols(); ++col)
        {
            tile.setPosition(sf::Vector2f(
                static_cast<float>(col) * tileSize,
                static_cast<float>(row) * tileSize));
            tile.setFillColor(colorForBiome(map.getCell(row, col).getBiome()));
            target.draw(tile);
        }
    }
}

sf::Color Renderer::colorForBiome(Biome biome)
{
    switch (biome)
    {
    case Biome::DeepOcean:  return sf::Color(30, 32, 117);  // Jacob's deep ocean
    case Biome::Ocean:      return sf::Color(0, 105, 148);  // Jacob's ocean
    case Biome::Coast:      return sf::Color(240, 230, 140);  // Jacob's coast
    case Biome::Beach:      return sf::Color(229, 216, 155);
    case Biome::Plains:     return sf::Color(132, 184, 69);
    case Biome::Forest:     return sf::Color(34, 139, 34);   // Jacob's forest
    case Biome::DeepForest: return sf::Color(16, 38, 17);   // Jacob's deep forest
    case Biome::Desert:     return sf::Color(181, 66, 51);   // Jacob's desert
    case Biome::Mountain:   return sf::Color(128, 128, 128);  // Jacob's mountain
    case Biome::Snow:       return sf::Color(239, 243, 247);
    case Biome::Count:      break;
    }
    return sf::Color::Magenta;
}