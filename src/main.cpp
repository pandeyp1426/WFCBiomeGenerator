#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

#include "../Graphics/mapRenderer.hpp"

int main()
{
    constexpr int   mapRows = 48;
    constexpr int   mapCols = 48;
    constexpr float tileSize = 16.0f;

    const auto windowWidth = static_cast<unsigned int>(static_cast<float>(mapCols) * tileSize);
    const auto windowHeight = static_cast<unsigned int>(static_cast<float>(mapRows) * tileSize);

    Map map(mapRows, mapCols);
    map.generate();

    Renderer renderer(tileSize);
    sf::RenderWindow window(
        sf::VideoMode({ windowWidth, windowHeight }),
        "WFC Biome Generator | attempts " +
        std::to_string(map.getGenerationAttempts()) +
        " | Space/R to regenerate");
    window.setFramerateLimit(60);

    const auto regenerate = [&]()
        {
            map.generate();
            window.setTitle(
                "WFC Biome Generator | attempts " +
                std::to_string(map.getGenerationAttempts()) +
                " | Space/R to regenerate");
        };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                continue;
            }

            const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
            if (!keyPressed)
                continue;

            switch (keyPressed->code)
            {
            case sf::Keyboard::Key::Escape:
                window.close();
                break;
            case sf::Keyboard::Key::Space:
            case sf::Keyboard::Key::R:
                regenerate();
                break;
            default:
                break;
            }
        }

        window.clear(sf::Color(14, 19, 28));
        renderer.draw(window, map);
        window.display();
    }

    return 0;
}