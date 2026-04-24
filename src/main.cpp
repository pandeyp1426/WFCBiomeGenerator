#include <SFML/Graphics.hpp>

#include <algorithm>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "../Graphics/renderer.hpp"

int main()
{
    constexpr int   mapRows = 48;
    constexpr int   mapCols = 48;
    constexpr float tileSize = 16.0f;

    const auto windowWidth = static_cast<unsigned int>(static_cast<float>(mapCols) * tileSize);
    const auto windowHeight = static_cast<unsigned int>(static_cast<float>(mapRows) * tileSize);

    std::mt19937 seedRng(std::random_device{}());
    const std::uint32_t startSeed = std::uniform_int_distribution<std::uint32_t>{}(seedRng);

    Map map(mapRows, mapCols, startSeed);
    map.resetToUncollapsed();

    // Pick a random starting position and a random starting biome
    std::uniform_int_distribution<int> rowDist(0, mapRows - 1);
    std::uniform_int_distribution<int> colDist(0, mapCols - 1);
    std::uniform_int_distribution<int> biomeDist(0, biomeCount() - 1);

    int cursorRow = rowDist(seedRng);
    int cursorCol = colDist(seedRng);
    const Biome startBiome = static_cast<Biome>(biomeDist(seedRng));
    map.paintCell(cursorRow, cursorCol, startBiome);

    // Collapse a single cell using DFA rules from its collapsed neighbors
    // Only collapses if not already collapsed
    const auto collapseCell = [&](int row, int col)
        {
            if (!map.isInBounds(row, col))
                return;

            Cell& cell = map.getCell(row, col);
            if (cell.isCollapsed())
                return;

            static constexpr int rowOffsets[4] = { -1, 0,  1,  0 };
            static constexpr int colOffsets[4] = { 0, 1,  0, -1 };

            // Intersect DFA allowed masks from all collapsed neighbors
            std::uint16_t allowedMask = fullBiomeMask();

            for (int dir = 0; dir < 4; ++dir)
            {
                const int nr = row + rowOffsets[dir];
                const int nc = col + colOffsets[dir];
                if (!map.isInBounds(nr, nc))
                    continue;

                const Cell& neighbor = map.getCell(nr, nc);
                if (!neighbor.isCollapsed())
                    continue;

                allowedMask &= BiomeDFA::allowedNeighborMask(
                    biomeMask(neighbor.getBiome()),
                    map.getBiomeRules());
            }

            // Collect valid biome options
            std::vector<Biome> options;
            for (int i = 0; i < biomeCount(); ++i)
            {
                if (allowedMask & biomeMask(static_cast<Biome>(i)))
                    options.push_back(static_cast<Biome>(i));
            }

            if (options.empty())
                options.push_back(Biome::Ocean); // fallback

            std::uniform_int_distribution<int> dist(0, static_cast<int>(options.size()) - 1);
            map.paintCell(row, col, options[static_cast<std::size_t>(dist(seedRng))]);
        };

    // Collapse the cursor cell itself + its 8 surrounding cells
    const auto collapseAround = [&](int row, int col)
        {
            // Collapse the cursor cell itself first
            collapseCell(row, col);

            // Then collapse all 8 surrounding cells
            for (int dr = -1; dr <= 1; ++dr)
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    if (dr == 0 && dc == 0)
                        continue;
                    collapseCell(row + dr, col + dc);
                }
            }
        };

    // Collapse around the starting position immediately on launch
    collapseAround(cursorRow, cursorCol);

    Renderer renderer(tileSize);
    sf::RenderWindow window(
        sf::VideoMode({ windowWidth, windowHeight }),
        "WFC Biome Generator | seed " + std::to_string(startSeed) + " | Arrows to explore");
    window.setFramerateLimit(60);

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

            int nextRow = cursorRow;
            int nextCol = cursorCol;

            switch (keyPressed->code)
            {
            case sf::Keyboard::Key::Escape:
                window.close();
                break;
            case sf::Keyboard::Key::Up:    --nextRow; break;
            case sf::Keyboard::Key::Down:  ++nextRow; break;
            case sf::Keyboard::Key::Left:  --nextCol; break;
            case sf::Keyboard::Key::Right: ++nextCol; break;
            default: break;
            }

            nextRow = std::clamp(nextRow, 0, mapRows - 1);
            nextCol = std::clamp(nextCol, 0, mapCols - 1);

            if (nextRow != cursorRow || nextCol != cursorCol)
            {
                cursorRow = nextRow;
                cursorCol = nextCol;

                // Only collapse if cursor landed on an uncollapsed cell
                if (!map.getCell(cursorRow, cursorCol).isCollapsed())
                    collapseAround(cursorRow, cursorCol);
            }
        }

        window.clear(sf::Color(14, 19, 28));
        renderer.draw(window, map);
        renderer.drawCursor(window, cursorRow, cursorCol,
            map.getCell(cursorRow, cursorCol).getBiome());
        window.display();
    }

    return 0;
}