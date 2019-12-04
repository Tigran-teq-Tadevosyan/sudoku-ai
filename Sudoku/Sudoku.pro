#-------------------------------------------------
#
# Project created by QtCreator 2019-11-15T02:54:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    AI/square.cpp \
    AI/grid.cpp \
    samplegrids.cpp \
    AI/goaltest.cpp \
    AI/solver.cpp \
    AI/gridgenerator.cpp \
    griditemdelegate.cpp \
    AI/localsearchsolver.cpp \
    AI/localsearchgrid.cpp \
    timer.cpp \
    AI/UniqueGenerator/uniquegenerator.cpp \
    AI/UniqueGenerator/chain.cpp \
    AI/UniqueGenerator/cell.cpp \
    AI/UniqueGenerator/cellpossiblevalues.cpp

HEADERS  += mainwindow.h \
    AI/square.h \
    AI/grid.h \
    config.h \
    samplegrids.h \
    AI/goaltest.h \
    AI/solver.h \
    AI/gridgenerator.h \
    griditemdelegate.h \
    AI/localsearchsolver.h \
    AI/localsearchgrid.h \
    timer.h \
    AI/UniqueGenerator/uniquegenerator.h \
    AI/UniqueGenerator/chain.h \
    AI/UniqueGenerator/cell.h \
    AI/UniqueGenerator/cellpossiblevalues.h

FORMS    += mainwindow.ui
