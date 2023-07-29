#include "chain.h"
#include <QDebug>
#include <iostream>

using namespace std;

Chain::Chain(std::vector<Cell *> &cellSet, Cell *startingCell, short value)
{
  values[0] = startingCell->value;
  values[1] = value;
  this->cellSet = cellSet;
  chainBeginning = startingCell;

  chainElements.push_back(startingCell);
  continueChainHorizontaly(chainBeginning, value);
}

Chain::Chain(std::vector<Cell *> &cellSet, Cell *startingCell)
{
  values[0] = startingCell->value;
  values[1] = -1;
  this->cellSet = cellSet;
  chainBeginning = startingCell;

  for(auto cellSetIterator = cellSet.begin(); cellSetIterator != cellSet.end(); ++cellSetIterator){
    Cell *currentCell = *cellSetIterator;
    if(currentCell->row == startingCell->row && currentCell->value != startingCell->value){
      values[1] = currentCell->value;

      chainElements.push_back(startingCell);
      continueChainHorizontaly(chainBeginning, values[1]);
      break;
    } else if(currentCell->col == startingCell->col && currentCell->value != startingCell->value){
      values[1] = currentCell->value;

      chainElements.push_back(startingCell);
      continueChainVertically(chainBeginning, values[1]);
      break;
    }
  }
}

bool Chain::operator <(const Chain &rhs)
{
  return this->getLength() < rhs.getLength();
}

short Chain::getLength() const
{
  return chainElements.size();
}

void Chain::printChain()
{
  cout<<"Values ("<< values[0]<<","<< values[1] << ") or ("<< values[1]<<","<< values[0] << ") " ;
  for(auto cellIterator = chainElements.begin(); cellIterator != chainElements.end(); ++ cellIterator){
    Cell* currentCellPtr = *cellIterator;
    cout<<"("<<currentCellPtr->row<<","<< currentCellPtr->col<<","<<currentCellPtr->value<<") -> ";
  }
  cout<<" Length: "<< getLength() <<endl;
}

short *Chain::getValues()
{
  return values;
}

bool Chain::areValues(short val1, short val2)
{
  return (val1 == values[0] && val2 == values[1]) || (val1 == values[1] && val2 == values[0]);
}

void Chain::expandStudiedFilledSets(std::vector<Cell *> &StudiedFilledSet, std::vector<Cell *> &StudiedBlankSet)
{
  StudiedFilledSet.push_back(chainElements.front());
  for(int index = 1; index < chainElements.size(); ++index){
    StudiedBlankSet.push_back(chainElements[index]);
  }
}

void Chain::removeChainElementsFromFormulationSet(vector<Cell *> &cellSet)
{
  for(auto cellSetIterator = cellSet.begin(); cellSetIterator != cellSet.end(); ++cellSetIterator){
    for(auto chainElementsIterator = chainElements.begin(); chainElementsIterator != chainElements.end(); ++chainElementsIterator){
      if(*cellSetIterator == *chainElementsIterator){
        cellSet.erase(cellSetIterator);
        --cellSetIterator;
      }
    }
  }
}

bool Chain::isEqual(const Chain &chain)
{
  if( (this->values[0] == chain.values[0] && this->values[1] == chain.values[1]) || (this->values[0] == chain.values[1] && this->values[1] == chain.values[0]) ){
    for(Cell* cell : chainElements){
      if(cell == chain.chainBeginning)
        return true;
    }
  }
  return false;
}

void Chain::continueChainHorizontaly(Cell *cellPtr, short value)
{
  for(auto cellElementPtr = cellSet.begin(); cellElementPtr != cellSet.end(); ++cellElementPtr){
    Cell* currentCellPtr = *cellElementPtr;
    if( currentCellPtr->value == value && currentCellPtr->row == cellPtr->row ){
        if( currentCellPtr == chainBeginning) return;
        chainElements.push_back(currentCellPtr);
        continueChainVertically(currentCellPtr, cellPtr->value);
        return;
    }
  }
}

void Chain::continueChainVertically(Cell *cellPtr, short value)
{
  for(auto cellElementPtr = cellSet.begin(); cellElementPtr != cellSet.end(); ++cellElementPtr){
    Cell* currentCellPtr = *cellElementPtr;
    if( currentCellPtr->value == value && currentCellPtr->col == cellPtr->col ){
        if( currentCellPtr == chainBeginning) return;
        chainElements.push_back(currentCellPtr);
        continueChainHorizontaly(currentCellPtr, cellPtr->value);
        return;
    }
  }
}

