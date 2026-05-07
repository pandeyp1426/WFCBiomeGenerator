#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cstdint>
#include <optional>
#include <random>
#include <string>

#include "../Graphics/button.hpp"
#include "../Graphics/mapRenderer.hpp"

int main()
{
    constexpr int   mapRows = 48;
    constexpr int   mapCols = 48;
    constexpr float tileSize = 16.0f;
    constexpr unsigned int sidebarWidth = 260;
    constexpr int minStepsPerFrame = 1;
    constexpr int maxStepsPerFrame = 200;

    const auto mapPixelWidth = static_cast<unsigned int>(static_cast<float>(mapCols) * tileSize);
    const auto windowWidth = mapPixelWidth + sidebarWidth;
    const auto windowHeight = static_cast<unsigned int>(static_cast<float>(mapRows) * tileSize);
    const float panelX = static_cast<float>(mapPixelWidth);
    const float controlX = panelX + 20.0f;

    std::uint32_t currentSeed = std::random_device{}();
    int stepsPerFrame = 20; // lower = slower, higher = faster
    Map map(mapRows, mapCols);
    map.startGeneration(currentSeed);
    bool generating = true;

    Renderer renderer(tileSize);
    Button restartButton(controlX, 24.0f, 210.0f, 44.0f, "Regenerate");
    Button newSeedButton(controlX, 176.0f, 210.0f, 38.0f, "New Seed");
    Button slowerButton(controlX, 330.0f, 96.0f, 38.0f, "Slower");
    Button fasterButton(controlX + 114.0f, 330.0f, 96.0f, 38.0f, "Faster");

    sf::Font panelFont;
    const char* fontPaths[] = {
        "Fonts/OpenSans.ttf",
        "Graphics/fonts/OpenSans.ttf",
        "../Graphics/fonts/OpenSans.ttf"
    };
    for (const char* fontPath : fontPaths)
    {
        if (panelFont.openFromFile(fontPath))
            break;
    }

    sf::Text seedTitle(panelFont, "Seed", 18);
    seedTitle.setFillColor(sf::Color(181, 231, 201));
    seedTitle.setPosition(sf::Vector2f(controlX, 94.0f));

    sf::Text seedValue(panelFont, "", 15);
    seedValue.setFillColor(sf::Color::White);
    seedValue.setPosition(sf::Vector2f(controlX, 124.0f));

    sf::Text speedTitle(panelFont, "Speed", 18);
    speedTitle.setFillColor(sf::Color(181, 231, 201));
    speedTitle.setPosition(sf::Vector2f(controlX, 248.0f));

    sf::Text speedValue(panelFont, "", 15);
    speedValue.setFillColor(sf::Color::White);
    speedValue.setPosition(sf::Vector2f(controlX, 278.0f));

    sf::RenderWindow window(
        sf::VideoMode({ windowWidth, windowHeight }),
        "WFC Biome Generator | Click Regenerate or press Space/R");
    window.setFramerateLimit(60);

    const auto restart = [&]()
        {
            map.startGeneration(currentSeed);
            generating = true;
            window.setTitle("WFC Biome Generator | Click Regenerate or press Space/R");
        };

    const auto updateSidebarText = [&]()
        {
            seedValue.setString(std::to_string(currentSeed));
            speedValue.setString(std::to_string(stepsPerFrame) + " steps / frame");
        };

    updateSidebarText();

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
                    mousePressed->button == sf::Mouse::Button::Left)
                {
                    const sf::Vector2f mousePosition = window.mapPixelToCoords(mousePressed->position);
                    if (restartButton.contains(mousePosition))
                    {
                        restart();
                    }
                    else if (newSeedButton.contains(mousePosition))
                    {
                        currentSeed = std::random_device{}();
                        updateSidebarText();
                        restart();
                    }
                    else if (slowerButton.contains(mousePosition))
                    {
                        stepsPerFrame = std::max(minStepsPerFrame, stepsPerFrame / 2);
                        updateSidebarText();
                    }
                    else if (fasterButton.contains(mousePosition))
                    {
                        stepsPerFrame = std::min(maxStepsPerFrame, stepsPerFrame * 2);
                        updateSidebarText();
                    }
                }
                continue;
            }

            switch (keyPressed->code)
            {
            case sf::Keyboard::Key::Escape:
                window.close();
                break;
            case sf::Keyboard::Key::Space:
                currentSeed = std::random_device{}();
                updateSidebarText();
                restart();
                break;
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
        newSeedButton.drawButton(window);
        slowerButton.drawButton(window);
        fasterButton.drawButton(window);
        window.draw(seedTitle);
        window.draw(seedValue);
        window.draw(speedTitle);
        window.draw(speedValue);
        window.display();
    }

    return 0;
}
