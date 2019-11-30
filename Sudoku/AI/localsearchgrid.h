#ifndef LOCALSEARCHGRID_H
#define LOCALSEARCHGRID_H

#include "config.h"
#include "grid.h"
#include <vector>

class LocalSearchGrid
{
public:
  LocalSearchGrid();
  LocalSearchGrid(Grid& copyGrid);
//  LocalSearchGrid(const LocalSearchGrid& copyGrid);

  bool operator <(const LocalSearchGrid& rhs);

  void fillEmptySquares();
  Grid *convertToGrid();

  int getCost() const;
  void doRandomSwap();
  void reverseLastSwap();

protected:
  void calculateCost();
  unsigned int getRowCost(short squareRow, short squareCol);
  unsigned int getColumnCost(short squareRow, short squareCol);
  unsigned int getSectionCost(short squareRow, short squareCol);

private:
  struct LocalSearchSquare{
    bool constant = false;
    short value = 0;
  };

  struct SquarePosition{
    short row;
    short column;
    SquarePosition(short _row = -1, short _column = -1) : row(_row), column(_column) {}
  };

  void swap(SquarePosition* position1, SquarePosition* position2);

  LocalSearchSquare grid[ROW_COUNT][COLUMN_COUNT];
  SquarePosition* swappablePositions[9][9];
  unsigned short swappablePositionsCount[9];
  unsigned int cost;
  SquarePosition lastSwapPositions[2];
};

#endif // LOCALSEARCHGRID_H
