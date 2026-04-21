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
    this->biomeOfCell = biomeOfCell;
    currentOptions = {biomeOfCell};
    numOfRemainingOptions = currentOptions.bucket_count(); // should be one since its predetermined 
    cellEntropy = 0.0; // Should be zero since it can't change since this is a user defined cell // not zero indicates its not set
    this->cellRow = inCellRow;
    this->cellCol = inCellCol;
}

/**
 * Updates the key-value pair based on if updateBool
 * 
 * This is will be used when backtracking to prevent the same option from being tried again
 * and also used when we need to update surrounding cells options based on the choice we made
 * 
 * it is able to be added back when we need to re-update the cells if we backtrack
 */
void Cell::updateOptions(char key, bool updateOptions){ 
    if(updateOptions){
        
    }
}

/**
 * sets the biome of cell
 * ensures its actually an option
 */
bool Cell::setBiomeOfCell(char chosenBiome) { 
    if(getCurrentOptions().at(chosenBiome)) {
        this->biomeOfCell = chosenBiome;
        updateOptions(chosenBiome, false); // false because this indicates it can't be chosen again and we are choosing it here
        return true;
    }
    else return false; 
}

void Cell::setCellEntropy(double inputEntropy) { this->cellEntropy = inputEntropy; }