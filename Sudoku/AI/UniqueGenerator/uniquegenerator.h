#ifndef UNIQUEGENERATOR_H
#define UNIQUEGENERATOR_H

#include "AI/grid.h"
#include "chain.h"
#include <map>
#include "config.h"

class UniqueGenerator
{
public:
  UniqueGenerator(Grid& grid);

  void moveRelatedValuesChainCells();
  void moveRandomValueCellsIntoStudiedBlankSet();
  void applyGreedyElimination();

  Grid& getGrid();

private:
  std::vector<Cell*> UnstudiedSet;
  std::vector<Cell*> StudiedFilledSet;
  std::vector<Cell*> StudiedBlankSet;

  std::vector<Chain*> chainSet;

  Grid exportGrid;

  short currentRelatedValues[2];

  void fillChainSetFromUnstudiedSet();
  Cell *fillPossibleValues(std::vector<Cell *> &temporaryInferableCellsList);
};

#endif // UNIQUEGENERATOR_H
