#include "timer.h"
#include <QDebug>

using namespace std;

Timer::Timer()
{

}

void Timer::start(string label)
{
  this->startTime = chrono::high_resolution_clock::now();
  this->label = label;
}

void Timer::end()
{
  qDebug()<<"Action '"<< this->label.c_str()<< "' took "<<(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - this->startTime)).count()<< " milliseconds to finish";
}


