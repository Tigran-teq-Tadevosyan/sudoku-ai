#ifndef GOALTEST_H
#define GOALTEST_H

#include <QObject>
#include "grid.h"
#include "config.h"

class GoalTest
{
public:
  GoalTest(Grid *grid);
  bool isSolved();

  static bool goalState(Grid* grid);

private:
  Grid* grid;
};

#endif // GOALTEST_H
