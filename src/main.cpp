#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

#include "../Graphics/button.hpp"
#include "../Graphics/mapRenderer.hpp"

int main()
{
    constexpr int   mapRows = 48;
    constexpr int   mapCols = 48;
    constexpr float tileSize = 16.0f;
    constexpr unsigned int sidebarWidth = 176;
    constexpr int   stepsPerFrame = 20; // lower = slower, higher = faster

    const auto mapPixelWidth = static_cast<unsigned int>(static_cast<float>(mapCols) * tileSize);
    const auto windowWidth = mapPixelWidth + sidebarWidth;
    const auto windowHeight = static_cast<unsigned int>(static_cast<float>(mapRows) * tileSize);

    Map map(mapRows, mapCols);
    map.startGeneration();
    bool generating = true;

    Renderer renderer(tileSize);
    Button restartButton(static_cast<float>(mapPixelWidth + 20), 24.0f, 136.0f, 44.0f, "Regenerate");

    sf::RenderWindow window(
        sf::VideoMode({ windowWidth, windowHeight }),
        "WFC Biome Generator | Click Regenerate or press Space/R");
    window.setFramerateLimit(60);

    const auto restart = [&]()
        {
            map.startGeneration();
            generating = true;
            window.setTitle("WFC Biome Generator | Click Regenerate or press Space/R");
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
            {
                const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>();
                if (mousePressed &&
                    mousePressed->button == sf::Mouse::Button::Left &&
                    restartButton.contains(window.mapPixelToCoords(mousePressed->position)))
                {
                    restart();
                }
                continue;
            }

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
                    window.setTitle("WFC Biome Generator | Done | Click Regenerate or press Space/R");
                    break;
                }
            }
        }

        window.clear(sf::Color(14, 19, 28));
        renderer.draw(window, map);
        restartButton.drawButton(window);
        window.display();
    }

    return 0;
}
