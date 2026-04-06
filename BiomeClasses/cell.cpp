#include <map>

class Cell{
    private:
        bool isSetByUser = false; // if this is true the cell cant change.
        std::map<char, bool> currentOptions = {{'O', true}, {'C', true}, {'P', true}}; // O = Ocean, C = Coast, P = Plains
        char biomeOfCell = NULL;
    
    public:
        Cell(bool isSetByUser){
            this->isSetByUser = isSetByUser;
        };

        


};