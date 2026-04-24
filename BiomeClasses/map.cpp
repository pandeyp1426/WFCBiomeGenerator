#include "map.hpp"

/**
 * Called only if the user defines any cells before hand
 * creates user defined cells only if true
 */
void Map::initializeBoard(bool isUserInput){
    if(isUserInput){ // creates user defined cells
        for(std::tuple<int,int,char> curTuple : userDefinedCells){
            mapVector.at(std::get<0>(curTuple)).at(std::get<1>(curTuple)) = new Cell(true, std::get<2>(curTuple));
        }
    }

    for(int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++){
            if(mapVector.at(row).at(col)){
                continue;
            }
            else mapVector.at(row).at(col) = new Cell();
        }
    }
}

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

double Map::cellOptions(int cellRow, int cellCol, Cell) {
	int amountOfOptions = 0;

    for (int row = cellRow - 1; row <= cellRow + 1; row++) {
        if (row >= 0 && row < numRows) {
            for (int col = cellCol - 1; col <= cellCol + 1; col++) {
                if (col >= 0 && col < numCols) {
                    if (mapVector.at(row).at(col)->getBiomeOfCell() != NULL) {
                        continue;
                    }
                    else {
                        char surroundingBiome = mapVector.at(row).at(col)->getBiomeOfCell();
                        std::vector<char> validOptions = mapRules[surroundingBiome];
                        for (char option : validOptions) {
                            if (mapVector.at(cellRow).at(cellCol)->getCurrentOptions(option)) {
                                amountOfOptions++;
                            }
						}
					}
                }
            }
        }
    }
    return amountOfOptions;
}

double Map::updateCellEntropy(int cellRow, int cellCol, int amountOfOptions) {
    // will become the total amount of options after checking all surrounding cells
    int amountOfOptions = mapVector.at(cellRow).at(cellCol)->getNumberOfRemainingOptions();
    int numSurroundingCells;

    std::unordered_map<char, std::set<char>> mapRules = {
        {'G', {'G', 'S'}},
        {'W', {'W', 'S'}},
        { 'S', {'G', 'W', 'S'}}
    };

    if (mapVector.at(cellRow).at(cellCol)->getBiomeOfCell() == 'G') {
		char currentBiome = mapRules.find('G');
    }
    else if (mapVector.at(cellRow).at(cellCol)->getBiomeOfCell() == 'W') {
        char currentBiome = mapRules.find('W');
    } 
    else if (mapVector.at(cellRow).at(cellCol)->getBiomeOfCell() == 'S') {
        char currentBiome = mapRules.find('S');
    }

    for (int row = cellRow - 1; row <= cellRow + 1; row++) {
        if (row >= 0 && row < numRows) {
            for (int col = cellCol - 1; col <= cellCol + 1; col++) {
                if (col >= 0 && col < numCols) {
                    if (mapVector.at(row).at(col)->getBiomeOfCell() != NULL) {
                        continue;
                    }
                    else if(currentBiome == 'G') {
						mapVector.at(cellRow).at(cellCol)->updateOptions('W', false);
                        amountOfOptions--;
                    }
                    else if(currentBiome == 'W') {
                        mapVector.at(cellRow).at(cellCol)->updateOptions('G', false);
                        amountOfOptions--;
                    }
                    else if(currentBiome == 'S') {
                        continue;
                    }
                }
            }
        }
    }
}


/**
 * Takes in size of the vector
 * userdefined cells is optional
 */
Map::Map(int numOfRows, int numOfCols, std::vector<std::tuple<int, int, char>> userDefinedCells = {{-1, -1, '0'}}){
    this->numRows = numOfRows;
    this->numCols = numOfCols;
    mapVector[numRows][numCols];
    std::tuple<int, int, char> tempTuple = userDefinedCells.at(0);
    if(std::get<0>(tempTuple) != -1){ // checking to see if user defined any cells
        this->userDefinedCells = userDefinedCells;
        initializeBoard(true);
    }
    else initializeBoard(false);

}

int Map::getNumRows(){ return numRows; }
int Map::getNumCols(){ return numCols; }

Cell* Map::getCell(int rowNum, int colNum){ return mapVector.at(rowNum).at(colNum); }

/**
 * Temporary print to cmd line to test
 * 
 * made before we have sfml going
 */
void Map::printMap(){
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            std::cout << mapVector.at(i).at(j)->getBiomeOfCell();
            if(j != numCols - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
}