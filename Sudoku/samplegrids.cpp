#include "samplegrids.h"


Grid SampleGrids::getSampleGrid1()
{
  Grid sampleGrid = Grid();
  sampleGrid.getSquarePtr(0,6)->setValue(6);
  sampleGrid.getSquarePtr(0,7)->setValue(8);
  sampleGrid.getSquarePtr(1,4)->setValue(7);
  sampleGrid.getSquarePtr(1,5)->setValue(3);
  sampleGrid.getSquarePtr(1,8)->setValue(9);
  sampleGrid.getSquarePtr(2,0)->setValue(3);
  sampleGrid.getSquarePtr(2,2)->setValue(9);
  sampleGrid.getSquarePtr(2,7)->setValue(4);
  sampleGrid.getSquarePtr(2,8)->setValue(5);
  sampleGrid.getSquarePtr(3,0)->setValue(4);
  sampleGrid.getSquarePtr(3,1)->setValue(9);
  sampleGrid.getSquarePtr(4,0)->setValue(8);
  sampleGrid.getSquarePtr(4,2)->setValue(3);
  sampleGrid.getSquarePtr(4,4)->setValue(5);
  sampleGrid.getSquarePtr(4,6)->setValue(9);
  sampleGrid.getSquarePtr(4,8)->setValue(2);
  sampleGrid.getSquarePtr(5,7)->setValue(3);
  sampleGrid.getSquarePtr(5,8)->setValue(6);
  sampleGrid.getSquarePtr(6,0)->setValue(9);
  sampleGrid.getSquarePtr(6,1)->setValue(6);
  sampleGrid.getSquarePtr(6,6)->setValue(3);
  sampleGrid.getSquarePtr(6,8)->setValue(8);
  sampleGrid.getSquarePtr(7,0)->setValue(7);
  sampleGrid.getSquarePtr(7,3)->setValue(6);
  sampleGrid.getSquarePtr(7,5)->setValue(8);
  sampleGrid.getSquarePtr(8,1)->setValue(2);
  sampleGrid.getSquarePtr(8,2)->setValue(8);
  return sampleGrid;
}

Grid SampleGrids::getSampleGrid2()
{
  Grid sampleGrid = Grid();
  sampleGrid.getSquarePtr(0,1)->setValue(2);
  sampleGrid.getSquarePtr(1,3)->setValue(6);
  sampleGrid.getSquarePtr(1,8)->setValue(3);
  sampleGrid.getSquarePtr(2,1)->setValue(7);
  sampleGrid.getSquarePtr(2,2)->setValue(4);
  sampleGrid.getSquarePtr(2,4)->setValue(8);
  sampleGrid.getSquarePtr(3,5)->setValue(3);
  sampleGrid.getSquarePtr(3,8)->setValue(2);
  sampleGrid.getSquarePtr(4,1)->setValue(8);
  sampleGrid.getSquarePtr(4,5)->setValue(4);
  sampleGrid.getSquarePtr(4,7)->setValue(1);
  sampleGrid.getSquarePtr(5,0)->setValue(6);
  sampleGrid.getSquarePtr(5,3)->setValue(5);
  sampleGrid.getSquarePtr(6,5)->setValue(1);
  sampleGrid.getSquarePtr(6,6)->setValue(7);
  sampleGrid.getSquarePtr(6,7)->setValue(8);
  sampleGrid.getSquarePtr(7,0)->setValue(5);
  sampleGrid.getSquarePtr(7,6)->setValue(9);
  sampleGrid.getSquarePtr(8,7)->setValue(4);
  return sampleGrid;
}

Grid SampleGrids::getSampleGrid3()
{
  Grid sampleGrid = Grid();
  sampleGrid.getSquarePtr(0,3)->setValue(6);
  sampleGrid.getSquarePtr(0,6)->setValue(4);
  sampleGrid.getSquarePtr(1,0)->setValue(7);
  sampleGrid.getSquarePtr(1,5)->setValue(3);
  sampleGrid.getSquarePtr(1,6)->setValue(6);
  sampleGrid.getSquarePtr(2,4)->setValue(9);
  sampleGrid.getSquarePtr(2,5)->setValue(1);
  sampleGrid.getSquarePtr(2,7)->setValue(8);
  sampleGrid.getSquarePtr(4,1)->setValue(5);
  sampleGrid.getSquarePtr(4,3)->setValue(1);
  sampleGrid.getSquarePtr(4,4)->setValue(8);
  sampleGrid.getSquarePtr(4,8)->setValue(3);
  sampleGrid.getSquarePtr(5,3)->setValue(3);
  sampleGrid.getSquarePtr(5,5)->setValue(6);
  sampleGrid.getSquarePtr(5,7)->setValue(4);
  sampleGrid.getSquarePtr(5,8)->setValue(5);
  sampleGrid.getSquarePtr(6,1)->setValue(4);
  sampleGrid.getSquarePtr(6,3)->setValue(2);
  sampleGrid.getSquarePtr(6,7)->setValue(6);
  sampleGrid.getSquarePtr(7,0)->setValue(9);
  sampleGrid.getSquarePtr(7,2)->setValue(3);
  sampleGrid.getSquarePtr(8,1)->setValue(2);
  sampleGrid.getSquarePtr(8,6)->setValue(1);
  return sampleGrid;
}
