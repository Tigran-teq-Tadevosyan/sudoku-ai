#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  currentGrid = SampleGrids::getSampleGrid1();
//  Solver solver = Solver(&sampleGrid);
//  solver.solve();
//  solver.printGrid();
  ui->setupUi(this);
//  QFont f("Ubuntu",15);
//  for(short row = 0; row < ROW_COUNT; ++row){
//    for(short col = 0; col < COLUMN_COUNT; ++col){
//        ui->GridDisplay->item(row, col)->setFont(f);
//    }
//  }
//  ui->GridDisplay->setColumnCount(9);
//  ui->GridDisplay->setRowCount(9);
//  ui->GridDisplay->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
//  ui->GridDisplay->verticalHeader()->setDefaultSectionSize(10);
//  ui->GridDisplay->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
//  ui->GridDisplay->horizontalHeader()->setDefaultSectionSize(10);
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
      QTableWidgetItem * item =  new QTableWidgetItem(QString::number(currentGrid.getSquare(row,col).getValue()));
      item->setTextAlignment(Qt::AlignCenter);
      item->setFont(fnt);
      ui->GridDisplay->setItem(row, col, item);
    }
    }
}

void MainWindow::SolveClicked()
{
  Solver solver = Solver(&currentGrid);
  solver.solve();
  currentGrid = solver.getGrid();
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
