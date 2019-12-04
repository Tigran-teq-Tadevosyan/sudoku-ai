#ifndef GRID_H
#define GRID_H

#include "config.h"
#include "square.h"

class Grid
{
public:
  Grid();
  void copy(Grid* original);
  Square getSquare(short row, short col) const;
  Square *getSquarePtr(short row, short col);
  bool checkIntegrity();

  void print();

private:
  Square grid[ROW_COUNT][COLUMN_COUNT];

  bool checkColumnIntegrity(short currentRow, short col);
  bool checkRawIntegrity(short row, short currentColumn);
  bool checkSectionIntegrity(short currentRow, short currentCol);
};

#endif // GRID_H
