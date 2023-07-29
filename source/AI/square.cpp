#include "square.h"
#include <algorithm>
#include <iostream>
#include "gridgenerator.h"

using namespace std;

Square::Square(){

}

bool Square::isCertain()
{
  return certain;
}

short Square::getValue()
{
  return value;
}

bool Square::setValue(short val)
{
  if(!certain && find(possibleValues.begin(), possibleValues.end(), val) != possibleValues.end()) {
      value = val;
      certain = true;
      return true;
  }

  return false;
}

bool Square::removePossibleValue(short val)
{
  for(auto ptr = possibleValues.begin(); ptr != possibleValues.end(); ++ptr ){
    if(*ptr == val){
      possibleValues.erase(ptr);
//      if(possibleValues.size() == 1){
//        setValue(possibleValues.front());
//      }
      return true;
    }
  }
  return false;
}

bool Square::isPossibleValue(short val)
{
  for(auto ptr = possibleValues.begin(); ptr != possibleValues.end(); ++ptr ){
    if(*ptr == val) return true;
  }
  return false;
}

short Square::setAnyPossibleValue()
{
  short val = 0;
  if(possibleValuesLeft())
    val = possibleValues.front();
  setValue(val);
  return val;
}

short Square::setRandomPossibleValue()
{
  short val = 0;
  if(possibleValuesLeft())
    val = possibleValues.at(GridGenerator::generateRandomNumber(0,possibleValues.size() - 1));
  setValue(val);
  return val;
}

bool Square::possibleValuesLeft()
{
  return possibleValues.size() != 0;
}

void Square::reverseSettelment()
{
  certain = false;
  removePossibleValue(value);
  value = 0;
}

void Square::removeValue()
{
  certain = false;
  possibleValues = {1,2,3,4,5,6,7,8,9};
  value = 0;
}

void Square::printPossibles()
{
  cout<<endl;
  for (std::vector<short>::const_iterator i = possibleValues.begin(); i != possibleValues.end(); ++i)
      std::cout << *i << ' ';
  cout<<endl;
}

void Square::setUniqueSolutionIfSo()
{
  if(possibleValues.size() == 1)
    setValue(possibleValues.front());
}


