#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer
{
public:
  Timer();
  void start(std::string label);
  void end();

private:
  std::string label;
  std::chrono::high_resolution_clock::time_point startTime;
};

#endif // TIMER_H
