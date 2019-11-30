#include "solver.h"
#include <cmath>
#include "goaltest.h"
#include <iostream>
#include <QDebug>

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

        if(checkColumn(row, col))
          changed = true;

        if(checkSection(row, col))
          changed = true;

        grid->getSquarePtr(row,col)->setUniqueSolutionIfSo();

        if(checkSectionPossibleCombinationUniqueness(row,col))
          changed = true;

        if(checkRowPossibleCombinationUniqueness(row,col))
          changed = true;

        if(checkColumnPossibleCombinationUniqueness(row,col))
          changed = true;
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
      }
    }
  }

  return changed;
}

bool Solver::checkSectionPossibleCombinationUniqueness(short currentRow, short currentCol)
{
  short rowBase = floor(currentRow/3)*3;
  short colBase = floor(currentCol/3)*3;

  Square * current = grid->getSquarePtr(currentRow, currentCol);
  if(current->isCertain()) return false;

  for(auto ptr = current->possibleValues.begin(); ptr != current->possibleValues.end(); ++ptr ){
    short possibleValue = *ptr;
    bool otherOptionsExist = false;
    for(short row = rowBase; row < ( rowBase + 3 ); ++row){
      for(short col = colBase; col < ( colBase + 3 ); ++col){
        if( !grid->getSquare(row, col).isCertain() && (row != currentRow || col != currentCol) ){
          vector<short> currentCellPossibleValues = grid->getSquarePtr(row,col)->possibleValues;

          for(auto currentPossiblePtr = currentCellPossibleValues.begin(); currentPossiblePtr != currentCellPossibleValues.end(); ++currentPossiblePtr ){
            if(*currentPossiblePtr == possibleValue){
              otherOptionsExist = true;
              goto JumpOutLabel;
            }
          }
        }
      }
    }
    JumpOutLabel:{}
    if(!otherOptionsExist){
      current->setValue(possibleValue);
      return true;
    }
  }
  return false;
}

bool Solver::checkRowPossibleCombinationUniqueness(short row, short currentCol)
{
  Square * current = grid->getSquarePtr(row, currentCol);
  if(current->isCertain()) return false;

  for(auto ptr = current->possibleValues.begin(); ptr != current->possibleValues.end(); ++ptr ){
    short possibleValue = *ptr;
    bool otherOptionsExist = false;

    for(short col = 0; col < COLUMN_COUNT; ++col){
      if( !grid->getSquare(row, col).isCertain() && col != currentCol){
        vector<short> currentCellPossibleValues = grid->getSquarePtr(row,col)->possibleValues;

        for(auto currentPossiblePtr = currentCellPossibleValues.begin(); currentPossiblePtr != currentCellPossibleValues.end(); ++currentPossiblePtr ){
          if(*currentPossiblePtr == possibleValue){
            otherOptionsExist = true;
            goto JumpOutLabel;
          }
        }
      }
    }
    JumpOutLabel:{}
    if(!otherOptionsExist){
      current->setValue(possibleValue);
      return true;
    }
  }
  return false;
}

bool Solver::checkColumnPossibleCombinationUniqueness(short currentRow, short col)
{
  Square * current = grid->getSquarePtr(currentRow, col);
  if(current->isCertain()) return false;

  for(auto ptr = current->possibleValues.begin(); ptr != current->possibleValues.end(); ++ptr ){
    short possibleValue = *ptr;
    bool otherOptionsExist = false;

    for(short row = 0; row < ROW_COUNT; ++row){
      if( !grid->getSquare(row, col).isCertain() && row != currentRow){
        vector<short> currentCellPossibleValues = grid->getSquarePtr(row,col)->possibleValues;

        for(auto currentPossiblePtr = currentCellPossibleValues.begin(); currentPossiblePtr != currentCellPossibleValues.end(); ++currentPossiblePtr ){
          if(*currentPossiblePtr == possibleValue){
            otherOptionsExist = true;
            goto JumpOutLabel;
          }
        }
      }
    }
    JumpOutLabel:{}
    if(!otherOptionsExist){
      current->setValue(possibleValue);
      return true;
    }
  }
  return false;
}

bool Solver::solve()
{
  if(GoalTest::goalState(grid)) return true;
  while(doInferanceCycle()){}
  return BackTrack();
}

bool Solver::randomSolve()
{
  if(GoalTest::goalState(grid)) return true;
  while(doInferanceCycle()){}
  return BackTrackWithRandomFills();
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
  qDebug()<<"BackTrack Cycle";
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

bool Solver::BackTrackWithRandomFills(){
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

        value = current->setRandomPossibleValue();
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
