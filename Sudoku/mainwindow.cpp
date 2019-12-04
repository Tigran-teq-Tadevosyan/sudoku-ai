#include "mainwindow.h"
#include <QDebug>
#include "griditemdelegate.h"
#include "AI/localsearchsolver.h"
#include "AI/localsearchgrid.h"
#include "AI/UniqueGenerator/uniquegenerator.h"
#include "timer.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  gridGenerator = GridGenerator();
  currentGrid = SampleGrids::getSampleGrid1();

  ui->setupUi(this);
  ui->GridDisplay->setItemDelegate(new GridItemDelegate(ui->GridDisplay));

  displayGrid();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::displayGrid()
{
  static QFont fnt;
  fnt.setPointSize(20);
  fnt.setFamily("Ubuntu");

  for(short row = 0; row < ROW_COUNT; ++row){
    for(short col = 0; col < COLUMN_COUNT; ++col){
      static QString cellValue;
      short val = currentGrid.getSquarePtr(row,col)->getValue();
      if(val == 0)
        cellValue = "";
      else
        cellValue = QString::number(val);
      QTableWidgetItem * item = new QTableWidgetItem(cellValue);
      item->setTextAlignment(Qt::AlignCenter);
      item->setFont(fnt);
      ui->GridDisplay->setItem(row, col, item);
    }
  }
}

void MainWindow::SolveClicked()
{
  Solver solver = Solver(&currentGrid);
  Timer timer;
  timer.start("Backtracking Solver");
  solver.solve();
  timer.end();
  currentGrid = solver.getGrid();
  displayGrid();
  qDebug()<<"cycles "<<solver.getCycles();
}

void MainWindow::LocalBeamSearchSolve()
{
  LocalSearchSolver* localSearchSolver = new LocalSearchSolver(currentGrid);
  localSearchSolver->solve();
  currentGrid = *localSearchSolver->getGrid();
  displayGrid();
}

void MainWindow::SampleGridChanged(int index)
{
  switch(index){
    case 0:
      currentGrid = SampleGrids::getSampleGrid1();
      break;
    case 1:
      currentGrid = SampleGrids::getSampleGrid2();
      break;
    case 2:
      currentGrid = SampleGrids::getSampleGrid3();
      break;
    default:
      currentGrid = SampleGrids::getSampleGrid1();
  }
  displayGrid();
}

void MainWindow::GenerateGrid()
{
  currentGrid = gridGenerator.generateGrid(ui->EmptyCellCountSpinBox->value());
  displayGrid();
}

void MainWindow::GenerateUniqueGrid()
{
  Timer timer;
  Grid grid;
  Solver solver = Solver(&grid);
  timer.start("Unique Generator");
  solver.randomSolve();
  UniqueGenerator uniqueGenerator(grid);
  timer.end();
  currentGrid = uniqueGenerator.getGrid();
  displayGrid();
}
