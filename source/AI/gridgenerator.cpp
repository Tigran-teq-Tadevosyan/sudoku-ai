#include "gridgenerator.h"
#include <cstdlib>
#include "config.h"
#include "solver.h"

using namespace std;

GridGenerator::GridGenerator()
{

}

Grid GridGenerator::generateGrid(short cellsLeftCout)
{
  grid = Grid();
  Solver solver = Solver(&grid);
  solver.randomSolve();
  int count = ROW_COUNT * COLUMN_COUNT - cellsLeftCout;
  while(count > 0){
    int row = getRandomCellValue();
    int col = getRandomCellValue();
    if(grid.getSquarePtr(row, col)->isCertain()){
      grid.getSquarePtr(row,col)->removeValue();
      count--;
    }
  }
  return grid;
}

void GridGenerator::fillGridWithValue(short val)
{
  vector<short> availableColumns = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
  for(short row = 0; row < ROW_COUNT; ++row){
    while(true){
      short index = generateRandomNumber(0 , availableColumns.size()-1 );
      short col = availableColumns.at(index);
      if(!grid.getSquarePtr(row,col)->isCertain()){
        availableColumns.erase(availableColumns.begin() + index);
        grid.getSquarePtr(row,col)->setValue(val);
        break;
      }
    }
  }
}

short GridGenerator::getRandomCellValue()
{
  return ( std::rand() % 9 );
}

short GridGenerator::generateRandomNumber(int lower_bound, int higher_bound)
{
  return ( std::rand() % ( higher_bound - lower_bound + 1 ) + lower_bound );
}
