#pragma once
#include "Task.hpp"

class DelayBufferTask : public Task<DelayBufferTask> {
public:
  DelayBufferTask(std::string key, Data::Ptr in, Data::Ptr out);
  ~DelayBufferTask();
  void run();
  void callback(int msg);
};