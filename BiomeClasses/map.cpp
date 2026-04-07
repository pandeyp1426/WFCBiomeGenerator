#include <vector>
#include <tuple>
#include "cell.cpp";

class Map{
    private:
        int numRows, numCols;
        std::vector<std::vector<Cell>> mapVector;
        std::vector<std::tuple<int, int, char>> userDefinedCells;

        /**
         * Called only if the user defines any cells before hand
         */
        void initializeBoard(){
            for(std::tuple<int, int, char> cell : userDefinedCells){
                mapVector.at(std::get<0>(cell)).at(std::get<1>(cell)) = Cell(true, std::get<2>(cell));
            }
        }

    public:
        Map(int numOfRows, int numOfCols, std::vector<std::tuple<int, int, char >> userDefinedCells = {{-1,-1, '0'}}){
            this->numRows = numOfRows;
            this->numCols = numOfCols;
            mapVector[numRows][numCols];

            if(userDefinedCells
            this->userDefinedCells = userDefinedCells;

        }

        int getNumRows(){ return numRows; }
        int getNumCols(){ return numCols; }

        Cell getCell(int rowNum, int colNum){ return mapVector.at(rowNum).at(colNum); }

};