#include "uniquegenerator.h"
#include <QDebug>
//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include "cellpossiblevalues.h"

using namespace std;

UniqueGenerator::UniqueGenerator(Grid &grid)
{
  StudiedBlankSet.clear();
  StudiedFilledSet.clear();
  UnstudiedSet.clear();
  for(unsigned short row = 0; row < ROW_COUNT; ++row){
    for(unsigned short col = 0; col < COLUMN_COUNT; ++col){
        UnstudiedSet.push_back(new Cell{row, col, static_cast<unsigned short>(grid.getSquarePtr(row,col)->getValue())});
    }
  }

  while(UnstudiedSet.size() > 0){
    fillChainSetFromUnstudiedSet();
    moveRelatedValuesChainCells();
    moveRandomValueCellsIntoStudiedBlankSet();
    applyGreedyElimination();
  }

  for(Cell *cell : StudiedFilledSet){
    exportGrid.getSquarePtr(cell->row,cell->col)->setValue(cell->value);
  }
}

void UniqueGenerator::moveRelatedValuesChainCells()
{
  for(auto chainSetIterator = chainSet.begin(); chainSetIterator != chainSet.end(); ++chainSetIterator){
    Chain *chain = *chainSetIterator;
    if(chain->areValues(currentRelatedValues[0],currentRelatedValues[1])){
      chain->expandStudiedFilledSets(StudiedFilledSet, StudiedBlankSet);
      chainSet.erase(chainSetIterator);
      --chainSetIterator;
    }
  }

  for(auto unstudiedSetIterator = UnstudiedSet.begin(); unstudiedSetIterator != UnstudiedSet.end(); ++unstudiedSetIterator){
    Cell *cell = *unstudiedSetIterator;
    if(cell->value == currentRelatedValues[0] || cell->value == currentRelatedValues[1])
      UnstudiedSet.erase(unstudiedSetIterator--);
  }

//  for(auto chainSetIterator = chainSet.begin(); chainSetIterator != chainSet.end(); ++chainSetIterator){
//    Chain *chain = *chainSetIterator;
//    chain->printChain();
  //  }
}

void UniqueGenerator::moveRandomValueCellsIntoStudiedBlankSet()
{
  short value = UnstudiedSet.front()->value;
  for(auto unstudiedSetIterator = UnstudiedSet.begin(); unstudiedSetIterator != UnstudiedSet.end(); ++unstudiedSetIterator){
    Cell *currentCell = *unstudiedSetIterator;
    if(currentCell->value == value){
      StudiedBlankSet.push_back(currentCell);
      UnstudiedSet.erase(unstudiedSetIterator);
      --unstudiedSetIterator;
    }
  }
}

void UniqueGenerator::applyGreedyElimination()
{
  vector<Cell*> temporaryInferableCellsList;
  Cell *cellWithHighestValueCount = nullptr;

  while(StudiedBlankSet.size() > 0){
    do{
      cellWithHighestValueCount = fillPossibleValues(temporaryInferableCellsList);
    } while( cellWithHighestValueCount == nullptr);

    StudiedBlankSet.erase(std::remove(StudiedBlankSet.begin(), StudiedBlankSet.end(), cellWithHighestValueCount), StudiedBlankSet.end());
    StudiedFilledSet.push_back(cellWithHighestValueCount);
  }

  for(Cell *cell : temporaryInferableCellsList){
    StudiedBlankSet.push_back(cell);
  }

  temporaryInferableCellsList.clear();
}

Grid &UniqueGenerator::getGrid()
{
  return exportGrid;
}

Cell* UniqueGenerator::fillPossibleValues(std::vector<Cell*> &temporaryInferableCellsList)
{
  int MaxPossibleCount = 0;
  bool wasInferedElement = false;
  Cell *cellWithHighestValueCount;
  CellPossibleValues cellPossibleValues;

  for(auto studiedBlankSetIterator = StudiedBlankSet.begin(); studiedBlankSetIterator != StudiedBlankSet.end(); ++studiedBlankSetIterator){
    Cell *currentCell = *studiedBlankSetIterator;

    for(Cell *cell : StudiedFilledSet){
      if(cell != currentCell && (cell->col == currentCell->col || cell->row == currentCell->row || (floor(cell->row/3) == floor(currentCell->row/3) && floor(cell->col/3) == floor(currentCell->col/3)) ) )
        cellPossibleValues.remove(cell->value);
        if(cellPossibleValues.isDefinite()){
          temporaryInferableCellsList.push_back(currentCell);
          StudiedBlankSet.erase(studiedBlankSetIterator);
          --studiedBlankSetIterator;
          wasInferedElement = true;
          goto ExitLabel;
        }
    }

    for(Cell *cell : temporaryInferableCellsList){
      if(cell != currentCell && (cell->col == currentCell->col || cell->row == currentCell->row || (floor(cell->row/3) == floor(currentCell->row/3) && floor(cell->col/3) == floor(currentCell->col/3)) ) )
        cellPossibleValues.remove(cell->value);
        if(cellPossibleValues.isDefinite()){
          temporaryInferableCellsList.push_back(currentCell);
          StudiedBlankSet.erase(studiedBlankSetIterator);
          --studiedBlankSetIterator;
          wasInferedElement = true;
          goto ExitLabel;
        }
    }
    if(MaxPossibleCount < cellPossibleValues.count()){
      MaxPossibleCount = cellPossibleValues.count();
      cellWithHighestValueCount = currentCell;
    }
    ExitLabel:{}
  }

  if(wasInferedElement) return nullptr;
  return cellWithHighestValueCount;
}
void UniqueGenerator::fillChainSetFromUnstudiedSet()
{
  for(Cell *currentCell : UnstudiedSet){
    for(short chainSecondValue = 1; chainSecondValue < 10; ++chainSecondValue){
      if(currentCell->value == chainSecondValue ) continue;

      chainSet.push_back(new Chain(UnstudiedSet, currentCell, chainSecondValue));
    }
  }

  for(int index = 0; index < chainSet.size(); ++index){
    for(auto chainSetIterator = chainSet.begin(); chainSetIterator != chainSet.end(); ++chainSetIterator){
      Chain *chain = *chainSetIterator;
      if(chain != chainSet[index] && chainSet[index]->isEqual(*chain)){
        chainSet.erase(chainSetIterator);
        chainSetIterator--;
      }
    }
  }

  sort(chainSet.begin(),chainSet.end(),Chain::compareChainPtr);

  currentRelatedValues[0] = chainSet.front()->getValues()[0];
  currentRelatedValues[1] = chainSet.front()->getValues()[1];
}


