#include "event_queue.h"

void EventQueue::run() {
  while (running_) {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this] { return !queue_.empty() || !running_; });

    while (!queue_.empty()) {
      auto task = std::move(queue_.front());
      queue_.pop();
      lock.unlock();

      try {
        task();
      } catch (...) {
        // Handle exceptions
      }

      lock.lock();
    }
  }
}

void EventQueue::stop() {
  running_ = false;
  condition_.notify_all();
}
