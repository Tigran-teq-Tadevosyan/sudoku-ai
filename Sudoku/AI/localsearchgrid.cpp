#include "localsearchgrid.h"
#include "square.h"
#include <QDebug>
#include "gridgenerator.h"
#include <algorithm>

using namespace std;

LocalSearchGrid::LocalSearchGrid()
{

}

LocalSearchGrid::LocalSearchGrid(Grid& copyGrid) : swappablePositionsCount{0}
{
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
        Square* squarePtr = copyGrid.getSquarePtr(row,col);
        if(squarePtr->isCertain()){
          grid[row][col].constant = true;
          grid[row][col].value = squarePtr->getValue();
        } else {
            swappablePositions[row][swappablePositionsCount[row]++] = new SquarePosition(row, col);
        }
    }
    }
}

bool LocalSearchGrid::operator <(const LocalSearchGrid &rhs)
{
  return this->getCost() < rhs.getCost();
}

void LocalSearchGrid::fillEmptySquares()
{
  for(short row = 0; row < ROW_COUNT; ++row){
    bool rowUnAvailableValues[COLUMN_COUNT] = {false};

    for(short col = 0; col < COLUMN_COUNT; ++col){
      if(grid[row][col].constant)
        rowUnAvailableValues[grid[row][col].value-1] = true;
    }

    for(short col = 0; col < COLUMN_COUNT; ++col){
      if(!grid[row][col].constant){
        for(int index = 0; index < COLUMN_COUNT; ++index){
          if(!rowUnAvailableValues[index]){
            grid[row][col].value = index + 1;
            rowUnAvailableValues[index] = true;
            break;
          }
        }
      }
    }
  }

  calculateCost();
}

Grid* LocalSearchGrid::convertToGrid()
{
  Grid* newGrid = new Grid();
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
        newGrid->getSquarePtr(row,col)->setValue(grid[row][col].value);
    }
  }
  return newGrid;
}

int LocalSearchGrid::getCost() const
{
  return cost;
}

void LocalSearchGrid::doRandomSwap()
{
  short row = GridGenerator::generateRandomNumber(0, ROW_COUNT-1);
  short index1 = GridGenerator::generateRandomNumber(0,swappablePositionsCount[row]-1);
  short index2 = -1;
  do {
    index2 = GridGenerator::generateRandomNumber(0,swappablePositionsCount[row]-1);
  } while(index1 == index2);
  swap(swappablePositions[row][index1],swappablePositions[row][index2]);
}

void LocalSearchGrid::reverseLastSwap()
{
  swap(&lastSwapPositions[0],&lastSwapPositions[1]);
}

void LocalSearchGrid::calculateCost()
{
  cost = 0;
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      cost += getColumnCost(row, col) + getSectionCost(row, col);
    }
  }
}

unsigned int LocalSearchGrid::getRowCost(short squareRow, short squareCol)
{
  unsigned int cost = 0;
  for(short col = 0; col < COLUMN_COUNT; ++col){
    if(squareCol != col && grid[squareRow][squareCol].value == grid[squareRow][col].value)
      ++cost;
  }
  return cost;
}

unsigned int LocalSearchGrid::getColumnCost(short squareRow, short squareCol)
{
  unsigned int cost = 0;
  for(short row = 0; row < COLUMN_COUNT; ++row){
    if(squareRow != row && grid[squareRow][squareCol].value == grid[row][squareCol].value)
      ++cost;
  }
  return cost;
}

unsigned int LocalSearchGrid::getSectionCost(short squareRow, short squareCol)
{
  unsigned int cost = 0;
  short rowBase = floor(squareRow/3)*3;
  short colBase = floor(squareCol/3)*3;

  for(short row = rowBase; row < ( rowBase + 3 ); ++row){
    for(short col = colBase; col < ( colBase + 3 ); ++col){
      if( (squareRow != row || squareCol != col) && grid[squareRow][squareCol].value == grid[row][col].value)
        ++cost;
    }
  }
  return cost;
}

void LocalSearchGrid::swap(LocalSearchGrid::SquarePosition *position1, LocalSearchGrid::SquarePosition *position2)
{
  short tempValue = grid[position1->row][position1->column].value;
  grid[position1->row][position1->column].value = grid[position2->row][position2->column].value;
  grid[position2->row][position2->column].value = tempValue;
  lastSwapPositions[0] = *position1;
  lastSwapPositions[1] = *position2;
  calculateCost();
}





