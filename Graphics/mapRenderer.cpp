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
            const Cell& cell = map.getCell(row, col);

            tile.setPosition(sf::Vector2f(
                static_cast<float>(col) * tileSize,
                static_cast<float>(row) * tileSize));

            tile.setFillColor(cell.isCollapsed()
                ? colorForBiome(cell.getBiome())
                : sf::Color(14, 19, 28));

            target.draw(tile);
        }
    }
}

sf::Color Renderer::colorForBiome(Biome biome)
{
    switch (biome)
    {
    case Biome::DeepOcean:  return sf::Color(30, 32, 117);
    case Biome::Ocean:      return sf::Color(0, 105, 148);
    case Biome::Coast:      return sf::Color(240, 230, 140);
    case Biome::Beach:      return sf::Color(229, 216, 155);
    case Biome::Plains:     return sf::Color(132, 184, 69);
    case Biome::Forest:     return sf::Color(34, 139, 34);
    case Biome::DeepForest: return sf::Color(16, 38, 17);
    case Biome::Desert:     return sf::Color(181, 66, 51);
    case Biome::Mountain:   return sf::Color(128, 128, 128);
    case Biome::Snow:       return sf::Color(239, 243, 247);
    case Biome::Count:      break;
    }
    return sf::Color::Magenta;
}