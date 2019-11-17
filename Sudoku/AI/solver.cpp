#include "solver.h"
#include <cmath>
#include "goaltest.h"
#include <iostream>

using namespace std;

Solver::Solver(Grid *grid)
{
  this->grid = grid;
}

bool Solver::doInferanceCycle()
{
  bool changed = false;

  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){

      if(checkRow(row, col))
        changed = true;
      if(grid->getSquare(row,col).isCertain()) continue;

      if(checkColumn(row, col))
        changed = true;
      if(grid->getSquare(row,col).isCertain()) continue;

      if(checkSection(row, col))
        changed = true;
      if(grid->getSquare(row,col).isCertain()) continue;
    }
  }

  return changed;
}

bool Solver::checkRow(short row, short currentColumn)
{
  bool changed = false;

  Square * current = grid->getSquarePtr(row,currentColumn);
  if(current->isCertain()) return false;

  for(short col = 0; col < COLUMN_COUNT; ++col){
    if(grid->getSquare(row,col).isCertain()){
      short val = grid->getSquare(row,col).getValue();
      changed = current->removePossibleValue(val);
      if(current->isCertain()) return true;
    }
  }

  return changed;
}

bool Solver::checkColumn(short currentRow, short col)
{
  bool changed = false;

  Square * current = grid->getSquarePtr(currentRow,col);
  if(current->isCertain()) return false;

  for(short row = 0; row < ROW_COUNT; ++row){
    if(grid->getSquare(row,col).isCertain()){
      short val = grid->getSquare(row,col).getValue();
      changed = current->removePossibleValue(val);
      if(current->isCertain()) return true;
    }
  }

  return changed;
}

bool Solver::checkSection(short currentRow, short currentCol)
{
  bool changed = false;
  short rowBase = floor(currentRow/3)*3;
  short colBase = floor(currentCol/3)*3;

  Square * current = grid->getSquarePtr(currentRow, currentCol);
  if(current->isCertain()) return false;

  for(short row = 0; row < 3; ++row){
    for(short col = 0; col < 3; ++col){
      if(grid->getSquare(rowBase + row, colBase + col).isCertain()){
        short val = grid->getSquare(rowBase + row, colBase + col).getValue();
        changed = current->removePossibleValue(val);
        if(current->isCertain()) return true;
      }
    }
  }

  return changed;
}

bool Solver::solve()
{
  doInferanceCycle();
  return BackTrack();
}

void Solver::printGrid()
{
  this->grid->print();
}

Grid Solver::getGrid()
{
  return *grid;
}


bool Solver::BackTrack(){
  static Square *current;
  short value = 0;
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      while(true){
        current = grid->getSquarePtr(row,col);
        if(current->isCertain())
          break;
        if(!current->possibleValuesLeft()) {
            return false;
        }

        value = current->setAnyPossibleValue();
        Grid *cloneGrid = new Grid();
        cloneGrid->copy(grid);
        if(value == 0) return false;

        while(doInferanceCycle()){}

        if(GoalTest::goalState(grid)) return true;
        if(BackTrack()) return true;

        grid->copy(cloneGrid);
        grid->getSquarePtr(row,col)->reverseSettelment();
      }
    }
  }
  return false;
}
