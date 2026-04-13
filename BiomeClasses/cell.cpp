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
    currentOptions = {{biomeOfCell, isSetByUser}};
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
void Cell::updateOptions(char key, bool updateBool){ 
    currentOptions.at(key) = updateBool;
    if(updateBool) numOfRemainingOptions++;
    else numOfRemainingOptions--;

}

bool Cell::getIsSetByUser() { return isSetByUser; }
// void setIsSetByUser(bool input) { isSetByUser = input; }

/**
 * This checks the current cell to see what options it has left
 * if it returns false the option isn't available
 */
bool Cell::getCurrentOptions(char key) { return currentOptions.at(key); }

int Cell::getNumberOfRemainingOptions() { return numOfRemainingOptions; }

char Cell::getBiomeOfCell() { return biomeOfCell; }

/**
 * sets the biome of the cell and ensures its reflected in current options
 */
void Cell::setBiomeOfCell(char chosenBiome) { 
    if(getCurrentOptions(chosenBiome)) {
        this->biomeOfCell = chosenBiome;
        updateOptions(chosenBiome, false); // false because this indicates it can't be chosen again and we are choosing it here
    }
    else return; 
}

double Cell::getCellEntropy() { return this->cellEntropy; }

void Cell::setCellEntropy(double inputEntropy) { this->cellEntropy = inputEntropy; }

std::vector<std::tuple<int, int, Cell*>>& Cell::getSurroundCellVect(){ return surroundingCells; }