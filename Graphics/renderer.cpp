#include "renderer.hpp"

Renderer::Renderer(float inTileSize) : tileSize(inTileSize), tileShape(sf::Vector2f(inTileSize, inTileSize))
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
                : sf::Color(14, 19, 28));  // dark = unexplored

            target.draw(tile);
        }
    }
}

void Renderer::drawCursor(sf::RenderTarget& target, int row, int col, Biome selectedBiome) const
{
    sf::RectangleShape cursor(sf::Vector2f(tileSize - 2.0f, tileSize - 2.0f));
    cursor.setPosition(sf::Vector2f(
        static_cast<float>(col) * tileSize + 1.0f,
        static_cast<float>(row) * tileSize + 1.0f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineThickness(2.0f);
    cursor.setOutlineColor(sf::Color::White);
    target.draw(cursor);

    sf::RectangleShape preview(sf::Vector2f(tileSize * 0.35f, tileSize * 0.35f));
    preview.setPosition(sf::Vector2f(
        static_cast<float>(col) * tileSize + 2.0f,
        static_cast<float>(row) * tileSize + 2.0f));
    preview.setFillColor(colorForBiome(selectedBiome));
    preview.setOutlineThickness(1.0f);
    preview.setOutlineColor(sf::Color(20, 20, 20, 220));
    target.draw(preview);
}

sf::Color Renderer::colorForBiome(Biome biome)
{
    switch (biome)
    {
    case Biome::Ocean:
        return sf::Color(35, 77, 196);
    case Biome::Coast:
        return sf::Color(73, 130, 228);
    case Biome::Beach:
        return sf::Color(229, 216, 155);
    case Biome::Plains:
        return sf::Color(132, 184, 69);
    case Biome::Forest:
        return sf::Color(27, 120, 33);
    case Biome::Desert:
        return sf::Color(204, 139, 62);
    case Biome::Mountain:
        return sf::Color(110, 110, 110);
    case Biome::Snow:
        return sf::Color(239, 243, 247);
    case Biome::Count:
        break;
    }

    return sf::Color::Magenta;
}