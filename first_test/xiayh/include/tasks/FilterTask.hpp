#pragma once
#include "Task.hpp"

class FilterTask : public Task<FilterTask> {
public:
  FilterTask(std::string key, Data::Ptr in, Data::Ptr out);
  ~FilterTask();
  void run();
  void callback(int msg);
};