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
            if(mapVector.at(row).at(col)){ // this should skip any cells that the user defined
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
void Map::updateCellEntropyChoice(int cellRow, int cellCol, char chosenBiome){

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
void Map::buildSurroundingCell(int cellRow, int cellCol, Cell* curCell){
    if(cellRow != 0 && cellRow != numRows - 1 && cellCol != 0 && cellCol != cellCol - 1){ // Cell is not an edge or corner
        curCell->getSurroundCellVect().push_back({cellRow-1, cellCol-1, getCell(cellRow-1, cellCol-1)}); // Top Left Cell
        curCell->getSurroundCellVect().push_back({cellRow-1, cellCol, getCell(cellRow-1, cellCol)}); // Top Middle Cell
        curCell->getSurroundCellVect().push_back({cellRow-1, cellCol+1, getCell(cellRow-1, cellCol+1)}); // Top Right Cell
        curCell->getSurroundCellVect().push_back({cellRow, cellCol, getCell(cellRow, cellCol)}); // Middle Left Cell
        curCell->getSurroundCellVect().push_back({cellRow, cellCol+1, getCell(cellRow, cellCol+1)}); // Middle Right Cell
        curCell->getSurroundCellVect().push_back({cellRow+1, cellCol-1, getCell(cellRow+1, cellCol-1)}); // Bottom Left Cell
        curCell->getSurroundCellVect().push_back({cellRow+1, cellCol-1, getCell(cellRow+1, cellCol)}); // Bottom Middle Cell
        curCell->getSurroundCellVect().push_back({cellRow+1, cellCol+1, getCell(cellRow+1, cellCol+1)}); // Bottom Right Cell
    }
    else if(cellRow == 0){ // cell is on the top edge
        curCell->getSurroundCellVect().push_back({cellRow+1, cellCol-1, getCell(cellRow+1, cellCol)}); // Bottom Middle Cell
        if(cellCol == 0){ // top left corner
            curCell->getSurroundCellVect().push_back({cellRow, cellCol+1, getCell(cellRow, cellCol+1)}); // Middle Right Cell
            curCell->getSurroundCellVect().push_back({cellRow+1, cellCol+1, getCell(cellRow+1, cellCol+1)}); // Bottom Right Cell
        }
        else if(cellCol == numCols - 1){ // top right corner
            curCell->getSurroundCellVect().push_back({cellRow+1, cellCol-1, getCell(cellRow+1, cellCol-1)}); // Bottom Left Cell
            curCell->getSurroundCellVect().push_back({cellRow, cellCol, getCell(cellRow, cellCol)}); // Middle Left Cell
        }
        else{ // cell is not top left or right corner
            curCell->getSurroundCellVect().push_back({cellRow+1, cellCol+1, getCell(cellRow+1, cellCol+1)}); // Bottom Right Cell
            curCell->getSurroundCellVect().push_back({cellRow+1, cellCol-1, getCell(cellRow+1, cellCol-1)}); // Bottom Left Cell
            curCell->getSurroundCellVect().push_back({cellRow, cellCol, getCell(cellRow, cellCol)}); // Middle Left Cell
            curCell->getSurroundCellVect().push_back({cellRow, cellCol+1, getCell(cellRow, cellCol+1)}); // Middle Right Cell
        }
    }
    else if(cellRow == numRows - 1){ // cell is on the bottom edge
        curCell->getSurroundCellVect().push_back({cellRow-1, cellCol, getCell(cellRow-1, cellCol)}); // Top Middle Cell
        if(cellCol == 0){ // Bottom left corner
            curCell->getSurroundCellVect().push_back({cellRow, cellCol+1, getCell(cellRow, cellCol+1)}); // Middle Right Cell
            curCell->getSurroundCellVect().push_back({cellRow-1, cellCol+1, getCell(cellRow-1, cellCol+1)}); // Top Right Cell
        }
        else if(cellCol == numCols-1){ // Bottom Right Corner
            curCell->getSurroundCellVect().push_back({cellRow, cellCol, getCell(cellRow, cellCol)}); // Middle Left Cell
            curCell->getSurroundCellVect().push_back({cellRow-1, cellCol-1, getCell(cellRow-1, cellCol-1)}); // Top Left Cell
        }
        else{ // cell is not bottom left or right corner
            curCell->getSurroundCellVect().push_back({cellRow, cellCol, getCell(cellRow, cellCol)}); // Middle Left Cell
            curCell->getSurroundCellVect().push_back({cellRow-1, cellCol-1, getCell(cellRow-1, cellCol-1)}); // Top Left Cell
            curCell->getSurroundCellVect().push_back({cellRow, cellCol+1, getCell(cellRow, cellCol+1)}); // Middle Right Cell
            curCell->getSurroundCellVect().push_back({cellRow-1, cellCol+1, getCell(cellRow-1, cellCol+1)}); // Top Right Cell   
        }
    }
    else if(cellCol == 0 && cellRow != 0 && cellRow != numRows - 1){ // Just Left Edge
        curCell->getSurroundCellVect().push_back({cellRow-1, cellCol, getCell(cellRow-1, cellCol)}); // Top Middle Cell
        curCell->getSurroundCellVect().push_back({cellRow-1, cellCol+1, getCell(cellRow-1, cellCol+1)}); // Top Right Cell
        curCell->getSurroundCellVect().push_back({cellRow+1, cellCol-1, getCell(cellRow+1, cellCol)}); // Bottom Middle Cell
        curCell->getSurroundCellVect().push_back({cellRow+1, cellCol+1, getCell(cellRow+1, cellCol+1)}); // Bottom Right Cell 
        curCell->getSurroundCellVect().push_back({cellRow, cellCol+1, getCell(cellRow, cellCol+1)}); // Middle Right Cell
    }
    else if(cellCol == numCols - 1 && cellRow != 0 && cellRow != numRows - 1){ // Just Right Edge
        curCell->getSurroundCellVect().push_back({cellRow-1, cellCol, getCell(cellRow-1, cellCol)}); // Top Middle Cell
        curCell->getSurroundCellVect().push_back({cellRow+1, cellCol-1, getCell(cellRow+1, cellCol)}); // Bottom Middle Cell
        curCell->getSurroundCellVect().push_back({cellRow, cellCol, getCell(cellRow, cellCol)}); // Middle Left Cell
        curCell->getSurroundCellVect().push_back({cellRow-1, cellCol-1, getCell(cellRow-1, cellCol-1)}); // Top Left Cell
        curCell->getSurroundCellVect().push_back({cellRow+1, cellCol-1, getCell(cellRow+1, cellCol-1)}); // Bottom Left Cell
    }
}


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

// run until Priority queue is emtpy
bool Map::generateMap(){
    while(!getPQ().empty()){
        Cell* topCell = getPQ().top().second;
        getPQ().pop();
        char biomeChoice = getNextBiomeChoice(topCell);
        if(biomeChoice = NULL){
            return false;
        }

        topCell->setBiomeOfCell(biomeChoice);
        // update cell options and entropy function
        for(int i = 0; i < topCell->getSurroundCellVect().size(); i++){
            Cell* curCell = (std::get<2>(topCell->getSurroundCellVect().at(i)));
            if(!curCell->getIsSetByUser() && curCell->getCellEntropy() != 0.0 /* && validChoice() */){ // push onto PQ if its not user defined and not already set = 0.0 entropy
                getPQ().push({curCell->getCellEntropy(), curCell});
            }
        }
    }

    return true;
}

/**
 * will return null char if the options are empty.
 * which shouldnt happen but allows for another spot/way to check that
 */
char Map::getNextBiomeChoice(Cell* curCell){
    const auto& cellBiomeOptions = curCell->getCurrentOptions();

    if(cellBiomeOptions.empty()){
        return '\0';
    }

    std::random_device randomSeed;
    std::mt19937 gen(randomSeed());
    std::uniform_int_distribution<> distr(0, curCell->getNumberOfRemainingOptions() - 1);

    auto it = cellBiomeOptions.begin();
    std::advance(it, distr(gen));
    return *it;
}