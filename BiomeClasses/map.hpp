#include <vector>
#include <tuple>
#include <iostream>
#include <set>
#include "cell.hpp"

class Map{
    private:
        int numRows, numCols;
        std::vector<std::vector<Cell*>> mapVector; // Store cell pointers so I could make initialize board the way i wanted too.
        std::vector<std::tuple<int, int, char>> userDefinedCells;

        /**
         * Called only if the user defines any cells before hand
         * creates user defined cells only if true
         */
        void initializeBoard(bool isUserInput);

        double updateCellEntropyChoice(int cellRow, int cellCol, char chosenBiome);

        std::unordered_map<char, std::set<char>> biomeRules = {
            {'C', {'C', 'D', 'O', 'P'}}, // Coast can be next to Coast/Desert/Ocean/Plains
            {'D', {'C', 'D', 'M'}},      // Desert can be next to Coast/Desert/Mountains
            {'F', {'F', 'P', 'M', 'I'}}, // Forest can be next to Forest/Plains/Mountains
            {'M', {'F', 'M', 'P', 'D'}}, // Mountains can be next to Forest/Mountains/Plains/Desert
            {'O', {'O', 'C', 'S'}},      // Ocean can be next to Ocean/Coast
            {'P', {'C', 'F', 'M', 'P'}}, // Plains can be next to Coast/Forest/Mountains/Plains
            {'I', {'I', 'F'}},           // Deep forest can be next to Forest/Deep Forest
            {'S', {'O', 'S'}}            // Deep Ocean can be next to Ocean/Deep Ocean
        };

        /**
         * this function should update the entropy of a single cell, so it would need to be called up to 8 times
         * when a choice is made. 
         * --------------------------------------------------------------------
         * | CellRow-1, cellCol-1 | CellRow-1, cellCol | cellRow-1, cellCol+1 |
         * --------------------------------------------------------------------
         * | CellRow  , cellcol-1 | cellrow  , cellCol | cellRow  , cellCol+1 |
         * --------------------------------------------------------------------
         * | CellRow+1, cellcol-1 | cellrow+1, cellCol | cellRow+1, cellCol+1 |
         * --------------------------------------------------------------------
         */
        double updateCellEntropy(int cellRow, int cellCol);
    
    public:
        Map(int numOfRows, int numOfCols, std::vector<std::tuple<int,int,char>> userDefinedCells = {{-1, -1, '0'}});
        
        int getNumRows();
        int getNumCols();

        Cell* getCell(int rowNum, int colNum);

        void printMap();


};