#include <map>

class Cell{
    private:
        bool isSetByUser = false; // if this is true the cell cant change.
        std::map<char, bool> currentOptions = {{'O', true}, {'C', true}, {'P', true}}; // O = Ocean, C = Coast, P = Plains
        char biomeOfCell = NULL;
    
    public:

        // default construtor
        Cell(){};

        
        /**
         * This constructor is used only if the cell is created by the user
         * for example they chose this cell before hitting start in our ui window eventually
         */
        Cell(bool isSetByUser, char biomeOfCell){
            this->isSetByUser = isSetByUser;
            this->biomeOfCell = biomeOfCell;
        };





};