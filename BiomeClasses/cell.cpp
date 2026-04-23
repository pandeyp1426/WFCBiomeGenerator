#include "cell.hpp"

// default construtor
Cell::Cell(int inCellRow, int inCellCol){
    this->cellRow = inCellRow;
    this->cellCol = inCellCol;
}

/**
 * This constructor is used only if the cell is created by the user
 * for example they chose this cell before hitting start in our ui window eventually
 */
Cell::Cell(bool isSetByUser, char biomeOfCell, int inCellRow, int inCellCol){
    this->isSetByUser = isSetByUser;
    this->isCellSet = isSetByUser;
    this->biomeOfCell = biomeOfCell;
    currentOptions = {biomeOfCell};
    numOfRemainingOptions = currentOptions.size(); // should be one since its predetermined 
    cellEntropy = 0.0; // Should be zero since it can't change since this is a user defined cell // not zero indicates its not set
    this->cellRow = inCellRow;
    this->cellCol = inCellCol;
}

/**
 * sets the biome of cell
 * returns false if it wasn't an option
 */
bool Cell::setBiomeOfCell(char chosenBiome) { 
    if(getCurrentOptions().count(chosenBiome) == 1) {
        this->biomeOfCell = chosenBiome;
        this->setIsCellSet(true);
        this->setCurrentOptions({chosenBiome});
        return true;
    }
    else return false; 
}

void Cell::setCellEntropy(double inputEntropy) { this->cellEntropy = inputEntropy; }