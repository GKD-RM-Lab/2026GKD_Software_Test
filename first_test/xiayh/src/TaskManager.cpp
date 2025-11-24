#include "common.hpp"
#include "tasks/TaskManager.hpp"
#include "tasks/DelayBufferTask.hpp"
#include <chrono>
#include <format>
#include <memory>
#include <string>
#include <thread>

using namespace std::chrono_literals;

extern std::unique_ptr<Logger> logger;

void TaskManager::set_input_data(Data::Val data) {
  *buffers[buffers.size() - 1].p_data = data;
}

Data::Val TaskManager::get_output_data() { return *buffers[0].p_data; }

void TaskManager::output_task() {
  std::thread([this]() {
    while (true) {
      Data::Val v;
      if ((v = *buffers[0].p_data) != 0) {
        *buffers[0].p_data = 0;
        logger->log(std::format("output: {}", std::to_string(v)));
      }
      std::this_thread::sleep_for(1ms);
    }
  }).detach();
}

void TaskManager::pop() {
  std::string key = buffers.back().key;
  logger->log(key);
  if (buffers.back().type == Filter) {
    logger->log("Filter");
    auto task = get_task<FilterTask>(key); 
    task.stop();
  }else if (buffers.back().type == Gain) {
    logger->log("Gain");
    auto task = get_task<GainTask>(key);
    task.stop();
  } else if (buffers.back().type == Delay) {
    logger->log("Delay");
    auto task = get_task<DelayBufferTask>(key);
    task.stop();
  } else {
    logger->log("?????");
  }
  tasks.erase(key);
  buffers.pop_back();
}
