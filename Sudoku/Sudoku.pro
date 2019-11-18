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
    AI/gridgenerator.cpp

HEADERS  += mainwindow.h \
    AI/square.h \
    AI/grid.h \
    config.h \
    samplegrids.h \
    AI/goaltest.h \
    AI/solver.h \
    AI/gridgenerator.h

FORMS    += mainwindow.ui
