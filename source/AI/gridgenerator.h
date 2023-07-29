#ifndef GRIDGENERATOR_H
#define GRIDGENERATOR_H

#include "grid.h"
#include "config.h"

class GridGenerator
{
public:
  GridGenerator();
  Grid generateGrid(short cellsLeftCout = GRID_CELL_DEFAULT_COUT);
  void fillGridWithValue(short val);

  static short getRandomCellValue();
  static short generateRandomNumber(int lower_bound, int higher_bound); // The number range does include bounds
private:
  Grid grid;
};

#endif // GRIDGENERATOR_H
