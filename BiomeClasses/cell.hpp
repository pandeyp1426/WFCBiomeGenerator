#pragma once
#include <vector>
#include <set>

class Cell {
    private:
        bool isSetByUser = false; // if this is true the cell shouldn't change.
        bool isCellSet = false;

        std::set<char> currentOptions = {'C', 'D', 'F', 'M', 'O', 'P', 'I', 'S'}; // O = Ocean, C = Coast, P = Plains // true means its available
        
        char biomeOfCell = '\0'; // this is the super position basically since it has no choice.
        
        int numOfRemainingOptions = currentOptions.size(); // just the amount of options in the unordered map // can just be the entropy of our cell
        
        double cellEntropy = 0.0; // will be this [this->numOfRemainingOptions + (numOfRemainingOptions of surrounding 8 cells)] / 9
        
        std::vector<std::tuple<int, int, Cell*>> surroundingCells;
        
        int cellRow, cellCol; // this is the cells coordinates in the map
    
    public:
        Cell(int cellRow, int cellCol);
        Cell(bool isSetByUser, char biomeOfCell, int cellRow, int cellCol);
        
        bool setBiomeOfCell(char chosenBiome);
        char getBiomeOfCell(){ return biomeOfCell; }

        double getCellEntropy(){ return cellEntropy; }
        void setCellEntropy(double inputEntropy);

        std::vector<std::tuple<int, int, Cell*>>& getSurroundCellVect() { return surroundingCells; }
        
        bool getIsSetByUser(){ return isSetByUser; }
       
        std::set<char>& getCurrentOptions(){ return currentOptions; }
        void setCurrentOptions(std::set<char> newBiomeOptions){ this->getCurrentOptions() = newBiomeOptions; }
        
        int getNumberOfRemainingOptions(){ return currentOptions.size(); }
       
        bool getIsCellSet(){ return this->isCellSet; }
        void setIsCellSet(bool isSet){ this->isCellSet = isSet; }
        
        std::pair<int,int> getCoords(){ return {cellRow, cellCol}; }
};