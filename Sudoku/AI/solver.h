#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>
#include "grid.h"
#include "../config.h"
#include "goaltest.h"

class Solver
{
public:
  Solver(Grid* grid);

  bool doInferanceCycle(); // Returns true if changes where made

  bool checkRow(short row, short currentColumn);
  bool checkColumn(short row, short currentColumn);
  bool checkSection(short row, short currentCol);

  bool solve();

  void printGrid();
  Grid getGrid();

  bool BackTrack();

private:
  Grid * grid;
//  GoalTest goalTest;
};

#endif // SOLVER_H
