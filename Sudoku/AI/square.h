#ifndef SQUARE_H
#define SQUARE_H

#include <vector>

class Square
{

public:
  Square();
  bool isCertain();
  short getValue();
  bool setValue(short val);
  bool removePossibleValue(short val); // returns true if val was removed from list
  bool isPossibleValue(short val);
  short setAnyPossibleValue();
  bool possibleValuesLeft();
  void reverseSettelment();
  void printPossibles();

  std::vector<short> possibleValues = {1,2,3,4,5,6,7,8,9};

private:
  bool certain = false;
  short value = 0;

};

#endif // SQUARE_H
