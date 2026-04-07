#include <unordered_map>

class Cell{
    private:
        bool isSetByUser = false; // if this is true the cell cant change.
        std::unordered_map<char, bool> currentOptions = {{'O', true}, {'C', true}, {'P', true}}; // O = Ocean, C = Coast, P = Plains // true means its available
        char biomeOfCell = NULL; // this is the super position basically since it has no choice.
        int numOfRemainingOptions = currentOptions.bucket_count(); // just the amount of options in the unordered map // can just be the entropy of our cell
        
    public:
        // default construtor
        Cell(){}
        
        /**
         * This constructor is used only if the cell is created by the user
         * for example they chose this cell before hitting start in our ui window eventually
         */
        Cell(bool isSetByUser, char biomeOfCell){
            this->isSetByUser = isSetByUser;
            this->biomeOfCell = biomeOfCell;
            currentOptions = {{biomeOfCell, isSetByUser}};
            numOfRemainingOptions = currentOptions.bucket_count();
        }
        
        /**
         * Updates the key-value pair based on if updateBool
         * 
         * This is will be used when backtracking to prevent the same option from being tried again
         * and also used when we need to update surrounding cells options based on the choice we made
         * 
         * it is able to be added back when we need to re-update the cells if we backtrack
         */
        void updateOptions(char key, bool updateBool){
            
            currentOptions.at(key) = updateBool;
            if(updateBool) numOfRemainingOptions++;
            else numOfRemainingOptions--;

        }

        bool getIsSetByUser() { return isSetByUser; }

        /**
         * This checks the current cell to see what options it has left
         * if it returns false the option isn't available
         */
        bool getCurrentOptions(char key){
            return currentOptions.at(key);
        }

        int getNumberOfRemainingOptions() { return numOfRemainingOptions; }

        char getBiomeOfCell() { return biomeOfCell; }

        /**
         * sets the biome of the cell and ensures its reflected in current options
         */
        void setBiomeOfCell(char chosenBiome) { 
            if(getCurrentOptions(chosenBiome)) {
                this->biomeOfCell = chosenBiome;
                updateOptions(chosenBiome, false); // false because this indicates it can't be chosen again and we are choosing it here
            }
            else return; 
        }
        






};