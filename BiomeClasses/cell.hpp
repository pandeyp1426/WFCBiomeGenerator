#pragma once
#include <unordered_map>
#include <vector>

class Cell {
    private:
        bool isSetByUser = false; // if this is true the cell cant change.
        std::unordered_map<char, bool> currentOptions = {{'O', true}, {'C', true}, {'P', true}}; // O = Ocean, C = Coast, P = Plains // true means its available
        char biomeOfCell = '\0'; // this is the super position basically since it has no choice.
        int numOfRemainingOptions = currentOptions.bucket_count(); // just the amount of options in the unordered map // can just be the entropy of our cell
        double cellEntropy; // will be this [this->numOfRemainingOptions + (numOfRemainingOptions of surrounding 8 cells)] / 9
        
        // this vector will hold the surrounding cells to reduce computations so we dont have to calculate this every time
        // might need to be a 2d vector that was the might be useless
        std::vector<Cell*> surroundingCells;
    
    public:
        Cell();
        Cell(bool isSetByUser, char biomeOfCell);

        void updateOptions(char key, bool updateBool);
        
        bool getIsSetByUser();
        bool getCurrentOptions(char key);
        int getNumberOfRemainingOptions();
        char getBiomeOfCell();
        void setBiomeOfCell(char chosenBiome);
        double getCellEntropy();
        void setCellEntropy(double inputEntropy);
        std::vector<Cell*> getSurroundCellVect();
};
