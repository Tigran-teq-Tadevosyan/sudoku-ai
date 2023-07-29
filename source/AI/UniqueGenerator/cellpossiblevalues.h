#ifndef CELLPOSSIBLEVALUES_H
#define CELLPOSSIBLEVALUES_H

#include <vector>

class CellPossibleValues
{
public:
  CellPossibleValues();
  void remove(short value);
  bool isDefinite();
  int count();
  short getValue(); // Returns the value if it is unique

private:
  std::vector<short> list {1,2,3,4,5,6,7,8,9};
};

#endif // CELLPOSSIBLEVALUES_H
