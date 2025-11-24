#include "Tasks/FilterTask.hpp"
#include "common.hpp"
#include <chrono>
#include <format>
#include <ios>
#include <iostream>
#include <memory>
#include <thread>


using namespace std::chrono_literals;

extern std::unique_ptr<Logger> logger;

FilterTask::FilterTask(std::string key, Data::Ptr in, Data::Ptr out)
    : Task<FilterTask>(key, in, out) {}
FilterTask::~FilterTask() {};

void FilterTask::run() {
  std::thread([this]() {
    while (true) {
      // std::cout << std::boolalpha << stop_ << std::endl;
      if (*stop_) {
        std::cout << "Ft stop" << std::endl;
        return;
      }
      Data::Val v;
      if ((v = take_in()) != None) {
        Data::Val res = v + 1;
        logger->log(std::format("write Filter-{}: {}", key_, res));
        set_out(res);
      }
      std::this_thread::sleep_for(1ms);
    }
  }).detach();
}

void FilterTask::callback(int msg) { set_in(msg); }
