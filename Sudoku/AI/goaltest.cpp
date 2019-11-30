#include "goaltest.h"

using namespace std;

GoalTest::GoalTest(Grid *grid)
{
  this->grid = grid;
}

bool GoalTest::isSolved()
{
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      if(!grid->getSquare(row,col).isCertain())
        return false;
    }
  }
  return true;
}

bool GoalTest::goalState(Grid *grid)
{
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      if(!grid->getSquare(row,col).isCertain())
        return false;
    }
  }
  return true;
}
