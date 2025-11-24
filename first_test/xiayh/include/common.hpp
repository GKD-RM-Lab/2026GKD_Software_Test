#pragma once
#include <chrono>
#include <deque>
#include <iostream>
#include <memory>
#include <thread>

using namespace std::chrono_literals;

struct Data {
  using Val = int;
  using Ptr = std::shared_ptr<std::atomic<Val>>;
  static inline Ptr create_ptr(Val v) {
    return std::make_shared<std::atomic<Val>>(v);
  }
};

enum TaskType {
  Filter,
  Gain,
  Delay,
  Other
};

class Logger {
private:
  std::deque<std::string> log_deque;

public:
  void log_task() {
    std::thread([this]() {
      while (true) {
        if (log_deque.empty()) {
          std::this_thread::sleep_for(1ms);
          continue;
        }
        std::cout << log_deque.front() << std::endl;
        log_deque.pop_front();

        std::this_thread::sleep_for(1ms);
      }
    }).detach();
  }

  void log(std::string msg) { log_deque.push_back(std::move(msg)); }
};