#include <vector>
#include "cell.cpp";

class Map{
    private:
        int numOfRows, numOfCols;
        std::vector<std::vector<Cell>> mapVector;

    public:
        Map(int numOfRows, int numOfCols){
            this->numOfRows = numOfRows;
            this->numOfCols = numOfCols;
            mapVector[numOfRows][numOfCols];
        }
};