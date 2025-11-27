#include "common.hpp"
#include "include/tasks/DelayBufferTask.hpp"
#include "include/tasks/GainTask.hpp"
#include "tasks/TaskManager.hpp"
#include <atomic>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

auto logger = std::make_unique<Logger>();
using namespace std::chrono_literals;
int main(int, char **) {
  logger->log_task();
  std::map<std::string, std::string> key2kind;
  auto tm = std::make_unique<TaskManager>();
  tm->output_task();
  //   tm->add_task<GainTask>("g");
  //   tm->add_task<FilterTask>("FA");
  //   tm->add_task<FilterTask>("FB");
  //   tm->add_task<GainTask>("GA");
  //   tm->get_task<GainTask>("GA").callback(2);
  //   tm->add_task<GainTask>("GB");
  //   tm->get_task<GainTask>("GB").callback(3);
  //   tm->add_task<DelayBufferTask>("DA");
  //   tm->add_task<DelayBufferTask>("DB");

  //   tm->set_input_data(20);

  std::this_thread::sleep_for(50ms);
  //   logger->log(std::to_string(tm->get_output_data()));

  std::string ipt;
  while (std::getline(std::cin, ipt)) {
    std::istringstream iss(ipt);
    std::string cmd;
    iss >> cmd;
    if (cmd == "add") {
      std::string key, kind;
      iss >> key >> kind;
      key2kind.emplace(key, kind);
      if (kind == "Filter")
        tm->add_task<FilterTask>(key);
      else if (kind == "Gain")
        tm->add_task<GainTask>(key);
      else if (kind == "Delay")
        tm->add_task<DelayBufferTask>(key);
    } else if (cmd == "pop") {

      tm->pop();

    } else if (cmd == "callback") {
      std::string key, msg;
      iss >> key >> msg;
      if (key2kind.at(key) == "Filter")
        tm->get_task<FilterTask>(key).callback(std::stoi(msg));
      else if (key2kind.at(key) == "Gain")
        tm->get_task<GainTask>(key).callback(std::stoi(msg));
      else if (key2kind.at(key) == "Delay")
        tm->get_task<DelayBufferTask>(key).callback(std::stoi(msg));
    }
  }

  return 0;
}
