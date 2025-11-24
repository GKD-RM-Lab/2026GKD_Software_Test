#include "Tasks/DelayBufferTask.hpp"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

extern std::unique_ptr<Logger> logger;

DelayBufferTask::DelayBufferTask(std::string key, Data::Ptr in, Data::Ptr out)
    : Task<DelayBufferTask>(key, in, out) {}
DelayBufferTask::~DelayBufferTask() {};

void DelayBufferTask::run() {
  std::thread([this]() {
    while (true) {
      if (stop_) {
        return;
      }
      Data::Val v;
      if ((v = take_in()) != None) {
        Data::Val res = v;
        set_out(res);
        logger->log(std::format("write Delay-{}: {}", key_, res));
        std::this_thread::sleep_for(1ms);

        res = v + 1;
        set_out(res);
        logger->log(std::format("write Delay-{}: {}", key_, res));
      }
      std::this_thread::sleep_for(1ms);
    }
  }).detach();
}

void DelayBufferTask::callback(int msg) { set_in(msg); }
