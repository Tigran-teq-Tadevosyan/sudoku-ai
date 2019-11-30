#ifndef LOCALSEARCHSOLVER_H
#define LOCALSEARCHSOLVER_H

#include "localsearchgrid.h"

class LocalSearchSolver
{
public:
  LocalSearchSolver(Grid& copyGrid);
  ~LocalSearchSolver();

  void generateNewRandomGrid();
  void solve();

  Grid *getGrid();
private:
  LocalSearchGrid * grid;
};

#endif // LOCALSEARCHSOLVER_H
