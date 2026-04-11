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
 * this function should update the entropy of current cells entropy and choice
 * I think we have to call this per surrounding cell.
 * --------------------------------------------------------------------
 * | cellRow-1, cellCol-1 | cellRow-1, cellCol | cellRow-1, cellCol+1 |
 * --------------------------------------------------------------------
 * | CellRow  , cellcol-1 | cellrow  , cellCol | cellRow  , cellCol+1 |
 * --------------------------------------------------------------------
 * | CellRow+1, cellcol-1 | cellrow+1, cellCol | cellRow+1, cellCol+1 |
 * --------------------------------------------------------------------
 */
void Map::updateCellEntropyChoice(int cellRow, int cellCol, char chosenBiome){
    int totalChoices;
}

void Map::buildSurroundingCell(int cellRow, int cellCol){
    // if top edge add bottom middle cell
        // if top left corner add middle right cell and bottom right cell
        // if top right corner add middle left cell and bottom left cell


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
