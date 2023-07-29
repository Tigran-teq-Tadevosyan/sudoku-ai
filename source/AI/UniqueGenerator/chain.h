#ifndef CHAIN_H
#define CHAIN_H

#include "cell.h"
#include <vector>

enum ChainPushStatus{
  Success = 0,
  Failure = 1,
  RepeatedCell = 2
};

class Chain
{
public:
  Chain(std::vector<Cell *> &cellSet, Cell* startingCell, short value);
  Chain(std::vector<Cell *> &cellSet, Cell* startingCell); // Same Constructor it just chooses available value for continuing the chain

  bool operator <(const Chain& rhs);

  short getLength() const;
  void printChain();

  short *getValues();
  bool areValues(short val1, short val2);

  void expandStudiedFilledSets(std::vector<Cell*> &StudiedFilledSet, std::vector<Cell*> &StudiedBlankSet);

  void removeChainElementsFromFormulationSet(std::vector<Cell *> &cellSet);
  bool isEqual(const Chain& chain);

  static bool compareChainPtr(Chain* a, Chain* b) { return (*b < *a); }

private:
  std::vector<Cell*> chainElements;
  std::vector<Cell*> cellSet;
  short values[2];
  Cell* chainBeginning;

  void continueChainHorizontaly(Cell* cellPtr, short value);
  void continueChainVertically(Cell* cellPtr, short value);
};

#endif // CHAIN_H
