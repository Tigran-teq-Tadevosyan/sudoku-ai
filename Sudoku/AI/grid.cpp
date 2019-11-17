#include "grid.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;

Grid::Grid()
{
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      grid[row][col] = *(new Square());
    }
  }
}

void Grid::copy(Grid *original)
{
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      //grid[row][col] = *(new Square());
      grid[row][col] = original->getSquare(row,col);
    }
  }
}
Square Grid::getSquare(short row, short col) const
{
  if(row < ROW_COUNT && row >= 0 && col < COLUMN_COUNT && col >= 0)
    return grid[row][col];
  throw out_of_range("Out of range row or column!s");
}

Square *Grid::getSquarePtr(short row, short col)
{
  if(row < ROW_COUNT && row >= 0 && col < COLUMN_COUNT && col >= 0)
    return &grid[row][col];
  throw out_of_range("Out of range row or column!s");
}

bool Grid::checkIntegrity()
{
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      if(!checkColumnIntegrity(row,col) || !checkRawIntegrity(row,col) || !checkSectionIntegrity(row,col))
        return false;
    }
  }
  return true;
}

void Grid::print()
{
  cout<<endl;
  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      cout<<grid[row][col].getValue()<<" ";
    }
    cout<<endl;
    }
}

bool Grid::checkColumnIntegrity(short currentRow, short col)
{
  Square * current = getSquarePtr(currentRow,col);
  if(!current->isCertain()) return true;

  for(short row = 0; row < ROW_COUNT; ++row){
    if(row != currentRow && getSquare(row,col).isCertain()){
      if(getSquare(row,col).getValue() == current->getValue() )
        return false;
    }
  }
  return true;
}

bool Grid::checkRawIntegrity(short row, short currentColumn)
{
  Square * current = getSquarePtr(row,currentColumn);
  if(!current->isCertain()) return true;

  for(short col = 0; col < COLUMN_COUNT; ++col){
    if(col != currentColumn && getSquare(row,col).isCertain()){
      if(getSquare(row,col).getValue() == current->getValue() )
        return false;
    }
  }
  return true;
}

bool Grid::checkSectionIntegrity(short currentRow, short currentCol)
{
  short rowBase = floor(currentRow/3)*3;
  short colBase = floor(currentCol/3)*3;

  Square * current = getSquarePtr(currentRow, currentCol);
  if(!current->isCertain()) return true;

  for(short row = 0; row < 3; ++row){
    for(short col = 0; col < 3; ++col){
      if( ( rowBase + row ) != currentRow && ( colBase + col ) != currentCol && getSquare(rowBase + row, colBase + col).isCertain()){
        if( getSquare(rowBase + row, colBase + col).getValue() == current->getValue() )
          return false;
      }
    }
  }
  return true;
}

