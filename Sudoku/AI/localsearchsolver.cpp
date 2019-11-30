#include "localsearchsolver.h"
#include "square.h"
#include <QDebug>
#include "gridgenerator.h"
#include <bits/stdc++.h>

using namespace std;

LocalSearchSolver::LocalSearchSolver(Grid& copyGrid)
{
  grid = new LocalSearchGrid(copyGrid);
}

LocalSearchSolver::~LocalSearchSolver()
{
  delete grid;
}

void LocalSearchSolver::solve()
{
//  LocalSearchGrid beamArray[5];
//  LocalSearchGrid beamDescendantsArray[30];
//  short cost = -1;
//  grid->fillEmptySquares();
//  for(unsigned short index = 0; index < 5; ++index)
//    beamArray[index] = *grid;


//  do {
//      beamDescendantsArray[0] = beamArray[0];
//      beamDescendantsArray[1] = beamArray[1];
//      beamDescendantsArray[2] = beamArray[2];
//      beamDescendantsArray[3] = beamArray[3];
//      beamDescendantsArray[4] = beamArray[4];
//    for(unsigned short index = 0; index < 5; ++index){
//      for(unsigned short tryCount = 0; tryCount < 5; ++tryCount){
//        beamDescendantsArray[(index+1) * 5 + tryCount] = beamArray[index];
//        beamDescendantsArray[(index+1) * 5 + tryCount].doRandomSwap();
//      }
//    }
//    sort(beamDescendantsArray, beamDescendantsArray + 30);
//    beamArray[0] = beamDescendantsArray[0];
//    beamArray[1] = beamDescendantsArray[1];
//    beamArray[2] = beamDescendantsArray[2];
//    beamArray[3] = beamDescendantsArray[3];
//    beamArray[4] = beamDescendantsArray[GridGenerator::generateRandomNumber(4,24)];
//    qDebug()<<"Cost -> "<<beamDescendantsArray[0].getCost();
//  } while(beamDescendantsArray[0].getCost() > 2);
//  grid = &beamDescendantsArray[0];

//  cost = grid->getCost();
//  while(cost > 8){
//    grid->doRandomSwap();
//    if(grid->getCost() > cost/* && GridGenerator::generateRandomNumber(1,20) > 1*/)
//      grid->reverseLastSwap();
//    cost = grid->getCost();
//    qDebug()<<"Cost "<<cost;
//  }
}

Grid *LocalSearchSolver::getGrid()
{
  return grid->convertToGrid();
}


