#pragma once
#include "DelayBufferTask.hpp"
#include "FilterTask.hpp"
#include "GainTask.hpp"
#include "common.hpp"
#include <atomic>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

class TaskManager {
private:
  using Task =
      std::variant<std::shared_ptr<FilterTask>, std::shared_ptr<GainTask>,
                   std::shared_ptr<DelayBufferTask>>;
  // Data::Ptr out = std::make_shared<std::atomic<Data::Val>>(0);
  std::map<std::string, Task> tasks;
  struct Buffer {
    Data::Ptr p_data;
    std::string key;
    TaskType type;
    Buffer(std::string key, Data::Ptr p_data, TaskType type) {
      this->p_data = p_data;
      this->key = std::move(key);
      this->type = type;
    }
  };
  std::vector<Buffer> buffers;

public:
  // std::vector<std::unique_ptr<std::pair<std::string, Task>>> tasks;
  TaskManager() {
    buffers.emplace_back("", std::make_shared<std::atomic<Data::Val>>(0),
                         TaskType::Other);
  }

  template <typename T> void add_task(std::string key) {
    if constexpr (std::is_same_v<T, FilterTask>) {
      buffers.emplace_back(key, std::make_shared<std::atomic<Data::Val>>(0),
                           TaskType::Filter);
    } else if constexpr (std::is_same_v<T, GainTask>) {
      buffers.emplace_back(key, std::make_shared<std::atomic<Data::Val>>(0),
                           TaskType::Gain);
    } else if constexpr (std::is_same_v<T, DelayBufferTask>) {
      buffers.emplace_back(key, std::make_shared<std::atomic<Data::Val>>(0),
                           TaskType::Gain);
    }
    auto task = std::make_shared<T>(key, buffers.back().p_data,
                                    buffers.at(buffers.size() - 2).p_data);
    task->run();
    // tasks.push_back(
    //     std::make_unique<std::pair<std::string, Task>>(key,
    //     std::move(task)));
    tasks.emplace(key, std::move(task));
  }

  template <typename T> T &get_task(std::string key) {
    return *std::get<std::shared_ptr<T>>(tasks.at(key));
  }

  void set_input_data(Data::Val data);
  Data::Val get_output_data();
  void output_task();
  void pop();
};