#include <SFML/Graphics.hpp>
#include <optional>
#include "Grid.hpp"

int main()
{
    constexpr int rows = 20;
    constexpr int cols = 20;
    constexpr float cellSize = 32.f;

    sf::RenderWindow window(
        sf::VideoMode({ static_cast<unsigned int>(cols * cellSize),
                       static_cast<unsigned int>(rows * cellSize) }),
        "WFC Biome Grid"
    );

    Grid grid(rows, cols);

    sf::RectangleShape cellShape({ cellSize - 1.f, cellSize - 1.f });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        for (int r = 0; r < grid.getRows(); ++r)
        {
            for (int c = 0; c < grid.getCols(); ++c)
            {
                cellShape.setPosition({ c * cellSize, r * cellSize });
                cellShape.setFillColor(biomeToColor(grid.getCell(r, c)));
                window.draw(cellShape);
            }
        }

        window.display();
    }

    return 0;
}