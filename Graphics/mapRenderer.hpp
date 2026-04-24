#pragma once
#include <SFML/Graphics.hpp>
#include "../BiomeClasses/map.hpp"
#include "../BiomeClasses/Biome.hpp"

class Map;
class Cell;

class MapRenderer{
    private:
        std::vector<std::vector<sf::RectangleShape>> displayMap;
        sf::RectangleShape borderRectangle;
        Map cellMap;
        std::vector<std::vector<Cell*>> mapOfCells;
        sf::RenderWindow currentWindow;
        int cellSize = 4;
        int numRows, numCols;

        void buildBorderRect();
        
        public:
        MapRenderer(int numRows, int numCols, std::vector<std::tuple<int,int,char>> userDefinedCells = {});
        void buildDisplayMap();
        void updateDisplayMap(int row, int col, sf::RenderWindow &window);
        void initialMapDraw(sf::RenderWindow &window);
        std::vector<std::vector<Cell*>> &getCellMap(){ return this->mapOfCells; }
        void generateMap(sf::RenderWindow &window);
        Map &getMap(){ return cellMap; }
};