#pragma once
#include "Task.hpp"

class GainTask : public Task<GainTask> {
private:
  int k = 1;

public:
  GainTask(std::string key, Data::Ptr in, Data::Ptr out);
  ~GainTask();
  void run();
  void callback(int msg);
};