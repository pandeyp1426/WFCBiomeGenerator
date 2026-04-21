#pragma once
#include <vector>
#include <tuple>
#include <iostream>
#include <queue>
#include "cell.hpp"

class Map{
    private:
        int numRows, numCols;
        std::vector<std::vector<Cell*>> mapVector; // Store cell pointers so I could make initialize board the way i wanted too.
        std::vector<std::tuple<int, int, char>> userDefinedCells;

        std::priority_queue<std::pair<double, Cell*>> mapGenerationPQ;

        /**
         * Called only if the user defines any cells before hand
         * creates user defined cells only if true
         */
        void initializeBoard(bool isUserInput);

        /**
         * this function should update the entropy of a single cell and all its surrounding cells
         * it should also update the choices of the surounding cells
         * --------------------------------------------------------------------
         * | CellRow-1, cellCol-1 | CellRow-1, cellCol | cellRow-1, cellCol+1 |
         * --------------------------------------------------------------------
         * | CellRow  , cellcol-1 | cellrow  , cellCol | cellRow  , cellCol+1 |
         * --------------------------------------------------------------------
         * | CellRow+1, cellcol-1 | cellrow+1, cellCol | cellRow+1, cellCol+1 |
         * --------------------------------------------------------------------
         */
        void updateCellEntropyChoice(int cellRow, int cellCol, char chosenBiome);

        /**
         * This needs to be called on every cell
         */
        void buildSurroundingCell(int cellRow, int cellCol, Cell* curCell);



    
    public:
        Map(int numOfRows, int numOfCols, std::vector<std::tuple<int,int,char>> userDefinedCells = {});
        
        int getNumRows(){ return numRows; }
        int getNumCols(){ return numCols; }

        Cell* getCell(int rowNum, int colNum);

        void printMap();

        bool generateMap();

        std::priority_queue<std::pair<double, Cell*>> getPQ(){ return this->mapGenerationPQ; }
};
