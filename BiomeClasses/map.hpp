#pragma once
#include <vector>
#include <tuple>
#include <iostream>
#include <queue>
#include <random>
#include <unordered_map>
#include "cell.hpp"


struct CompareCells{
    bool operator()(const std::pair<double, Cell*>& a,
                    const std::pair<double, Cell*>& b) const {
        return a.first > b.first;
    }
};

class Map{
    private:
        int numRows, numCols;
        std::vector<std::vector<Cell*>> mapVector; // Store cell pointers so I could make initialize board the way i wanted too.
        std::vector<std::tuple<int, int, char>> userDefinedCells;
        std::priority_queue<std::pair<double, Cell*>, std::vector<std::pair<double, Cell*>>, CompareCells> mapGenerationPQ;
        std::unordered_map<char, std::set<char>> biomeRules = {
            {'O', {'O', 'C'}},           // Ocean can be next to Ocean/Coast
            {'C', {'C', 'D', 'O', 'P'}}, // Coast can be next to Coast/Desert/Ocean/Plains
            {'P', {'C', 'F', 'M', 'P'}}, // Plains can be next to Coast/Forest/Mountains/Plains
            {'F', {'F', 'P', 'M'}},      // Forest can be next to Forest/Plains/Mountains
            {'M', {'F', 'M', 'P', 'D'}}, // Mountains can be next to Forest/Mountains/Plains/Desert
            {'D', {'C', 'D', 'M'}}       // Desert can be next to Coast/Desert/Mountains
        };

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
        void updateCellChoice(Cell* currentCell);

        void updateCellEntropy(Cell* currentCell);

        /**
         * This needs to be called on every cell
         */
        void buildSurroundingCell(int cellRow, int cellCol, Cell* curCell);

        void initializePriorityQueue(bool hasUserDefinedCells);

    public:
        Map(int numOfRows, int numOfCols, std::vector<std::tuple<int,int,char>> userDefinedCells = {});
        
        int getNumRows(){ return numRows; }
        int getNumCols(){ return numCols; }

        std::vector<char> biomeChoices = {'O', 'C', 'P'};

        Cell* &getCell(int rowNum, int colNum){ return mapVector.at(rowNum).at(colNum); }

        void printMap();

        void generateMap();

        char getNextBiomeChoice(Cell* curCell);

        std::priority_queue<std::pair<double, Cell*>, std::vector<std::pair<double, Cell*>>, CompareCells> &getPQ(){ return this->mapGenerationPQ; }

        std::set<char> getBiomeRules(char chosenBiome){ return this->biomeRules.at(chosenBiome); }

        void pushCellToPQ(Cell* pushCell);
};
