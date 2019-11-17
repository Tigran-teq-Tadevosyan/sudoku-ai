#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "samplegrids.h"
#include <iostream>
#include "AI/solver.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void displayGrid();

public slots:
  void SolveClicked();
  void SampleGridChanged(int index);

private:
  Ui::MainWindow *ui;
  Grid currentGrid;
};

#endif // MAINWINDOW_H
