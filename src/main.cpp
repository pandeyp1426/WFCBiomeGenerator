#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

#include "../Graphics/mapRenderer.hpp"

int main()
{
    constexpr int   mapRows = 48;
    constexpr int   mapCols = 48;
    constexpr float tileSize = 16.0f;
    constexpr int   stepsPerFrame = 20; // lower = slower, higher = faster

    const auto windowWidth = static_cast<unsigned int>(static_cast<float>(mapCols) * tileSize);
    const auto windowHeight = static_cast<unsigned int>(static_cast<float>(mapRows) * tileSize);

    Map map(mapRows, mapCols);
    map.startGeneration();
    bool generating = true;

    Renderer renderer(tileSize);
    sf::RenderWindow window(
        sf::VideoMode({ windowWidth, windowHeight }),
        "WFC Biome Generator | Space/R to regenerate");
    window.setFramerateLimit(60);

    const auto restart = [&]()
        {
            map.startGeneration();
            generating = true;
            window.setTitle("WFC Biome Generator | Space/R to regenerate");
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
                restart();
                break;
            default:
                break;
            }
        }

        // Collapse stepsPerFrame cells per frame so generation is visible
        if (generating)
        {
            for (int i = 0; i < stepsPerFrame; ++i)
            {
                if (!map.generateStep())
                {
                    generating = false;
                    window.setTitle("WFC Biome Generator | Done | Space/R to regenerate");
                    break;
                }
            }
        }

        window.clear(sf::Color(14, 19, 28));
        renderer.draw(window, map);
        window.display();
    }

    return 0;
}