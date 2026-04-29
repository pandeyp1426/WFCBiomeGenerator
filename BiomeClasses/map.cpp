#include "map.hpp"

/**
 * Takes in size of the vector
 * userdefined cells is optional
 */
Map::Map(int numOfRows, int numOfCols, std::vector<std::tuple<int, int, char>> userDefinedCells){
    this->numRows = numOfRows;
    this->numCols = numOfCols;
    mapVector.resize(numRows, std::vector<Cell*>(numCols, nullptr));

    if(!userDefinedCells.empty()){ // checking to see if user defined any cells
        this->userDefinedCells = userDefinedCells;
        initializeBoard(true);
    }
    else initializeBoard(false);
}

/**
 * Called only if the user defines any cells before hand
 * creates user defined cells only if true
 */
void Map::initializeBoard(bool isUserInput){
    if(isUserInput){ // creates user defined cells if true
        for(std::tuple<int,int,char> curTuple : userDefinedCells){
            mapVector.at(std::get<0>(curTuple)).at(std::get<1>(curTuple)) = new Cell(true, std::get<2>(curTuple), std::get<0>(curTuple), std::get<1>(curTuple));
        }
    }

    for(int row = 0; row < numRows; row++){ // builds the rest of the cells with default constructro
        for(int col = 0; col < numCols; col++){
            if(mapVector.at(row).at(col)){
                continue;
            }
            else mapVector.at(row).at(col) = new Cell(row, col);
        }
    }

    for(int row = 0; row < numRows; row++){ // goes through board again after all cells are created buildingSurroundingCellsVect
        for(int col = 0; col < numCols; col++){
            buildSurroundingCell(row, col, getCell(row, col));
        }
    }
}

/**
 * this function should update the entropy of current cells entropy and choices
*/
double Map::updateCellEntropyChoice(int cellRow, int cellCol){
    cellEntropy = 6.0; //6 because there are 6 options
    for (int row = cellRow - 1; row <= cellRow + 1; row++) {
        if (row >= 0 && row < numRows) {
            for (int col = cellCol - 1; col <= cellCol + 1; col++) {
                if (col >= 0 && col < numCols) {
                    if (mapVector.at(rowNum).at(colNum)) {
                    }
                }
            }
        }
    }
    return entropy;
}

/**
 * this function builds the Cell*'s surrounding cells vector, that way when we update a cells entropy and biome choice
 * we can easily update its surrounding cells by just iterating through the cells surroundingCells Vector.
 * --------------------------------------------------------------------
 * | cellRow-1, cellCol-1 | cellRow-1, cellCol | cellRow-1, cellCol+1 |
 * --------------------------------------------------------------------
 * | CellRow  , cellcol-1 | cellrow  , cellCol | cellRow  , cellCol+1 |
 * --------------------------------------------------------------------
 * | CellRow+1, cellcol-1 | cellrow+1, cellCol | cellRow+1, cellCol+1 |
 * --------------------------------------------------------------------
 */

void Map::buildSurroundingCell(int cellRow, int cellCol, Cell *curCell) {
    for(int row = cellRow - 1; row <= cellRow + 1; row++){
        for(int col = cellCol - 1; col <= cellCol + 1; col++){
            
        }
    }
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