#include "../Graphics/mapRenderer.hpp"

MapRenderer::MapRenderer(int numRows, int numCols, std::vector<std::tuple<int,int,char>> userDefinedCells) : 
cellMap(numRows, numCols, userDefinedCells){
    this->mapOfCells = cellMap.getMap();
    buildDisplayMap();
    this->numRows = numRows;
    this->numCols = numCols;
    buildBorderRect();
}

void MapRenderer::buildDisplayMap(){
    displayMap.resize(mapOfCells.size(), std::vector<sf::RectangleShape>(mapOfCells.at(0).size()));

    for(int row = 0; row < mapOfCells.size(); row++){
        for(int col = 0; col < mapOfCells.at(row).size(); col++){
            Cell* curCell = cellMap.getCell(row, col);

            sf::RectangleShape newRect;
            newRect.setSize(sf::Vector2f(cellSize,cellSize));
            newRect.setPosition({static_cast<float>(row) * cellSize + 4, static_cast<float>(col) * cellSize + 4});
            newRect.setFillColor(biomeToColor(curCell->getBiomeOfCell()));
            displayMap.at(row).at(col) = newRect;
        }
    }
}

void MapRenderer::updateDisplayMap(int row, int col, sf::RenderWindow &window){
    Cell* curCell = cellMap.getCell(row, col);
    displayMap.at(row).at(col).setFillColor(biomeToColor(curCell->getBiomeOfCell()));
    window.draw(displayMap.at(row).at(col));
    window.draw(borderRectangle);
}

void MapRenderer::initialMapDraw(sf::RenderWindow &window){
    for(int row = 0; row < displayMap.size(); row++){
        for(int col = 0; col < displayMap.at(row).size(); col++){
            window.draw(displayMap.at(row).at(col));
        }
    }
    window.draw(borderRectangle);
}

void MapRenderer::generateMap(sf::RenderWindow &window){
    std::pair<int, int> curCoords = cellMap.generateMap();
    updateDisplayMap(curCoords.first, curCoords.second, window);
}

void MapRenderer::buildBorderRect(){
    this->borderRectangle.setSize(sf::Vector2f(numRows * 4, numCols * cellSize));
    this->borderRectangle.setOutlineColor(sf::Color::Black);
    this->borderRectangle.setOutlineThickness(4);
    this->borderRectangle.setFillColor(sf::Color::Transparent);
    this->borderRectangle.setPosition(sf::Vector2f(4, 4));
}