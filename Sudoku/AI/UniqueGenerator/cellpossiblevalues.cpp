#include "cellpossiblevalues.h"
#include <algorithm>

using namespace std;

CellPossibleValues::CellPossibleValues()
{

}

void CellPossibleValues::remove(short value)
{
  list.erase(std::remove(list.begin(), list.end(), value), list.end());
}

bool CellPossibleValues::isDefinite()
{
  return list.size() == 1;
}

int CellPossibleValues::count()
{
  return list.size();
}

short CellPossibleValues::getValue()
{
  if(isDefinite())
    return list.front();
  return 0;
}
