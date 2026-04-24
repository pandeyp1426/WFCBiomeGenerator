#include "../Graphics/mapRenderer.hpp"
#include "../BiomeClasses/map.hpp"
#include "../BiomeClasses/cell.hpp"
#include "../BiomeClasses/Biome.hpp"

MapRenderer::MapRenderer(int numRows, int numCols, std::vector<std::tuple<int,int,char>> userDefinedCells) : 
cellMap(numRows, numCols, userDefinedCells){
    this->mapOfCells = cellMap.getMap();
    buildDisplayMap();
}

void MapRenderer::buildDisplayMap(){
    displayMap.resize(mapOfCells.size(), std::vector<sf::RectangleShape>(mapOfCells.at(0).size()));

    for(int row = 0; row < mapOfCells.size(); row++){
        for(int col = 0; col < mapOfCells.at(row).size(); col++){
            Cell* curCell = cellMap.getCell(row, col);

            sf::RectangleShape newRect;
            newRect.setSize(sf::Vector2f(cellSize,cellSize));
            newRect.setPosition({static_cast<float>(row) * cellSize, static_cast<float>(col) * cellSize});
            newRect.setFillColor(biomeToColor(curCell->getBiomeOfCell()));
            displayMap.at(row).at(col) = newRect;
        }
    }
}

void MapRenderer::updateDisplayMap(int row, int col, sf::RenderWindow &window){
    Cell* curCell = cellMap.getCell(row, col);
    displayMap.at(row).at(col).setFillColor(biomeToColor(curCell->getBiomeOfCell()));
    window.draw(displayMap.at(row).at(col));
}

void MapRenderer::initialMapDraw(sf::RenderWindow &window){
    for(int row = 0; row < displayMap.size(); row++){
        for(int col = 0; col < displayMap.at(row).size(); col++){
            window.draw(displayMap.at(row).at(col));
        }
    }
}

void MapRenderer::generateMap(sf::RenderWindow &window){
    std::pair<int, int> curCoords = cellMap.generateMap();
    updateDisplayMap(curCoords.first, curCoords.second, window);
}