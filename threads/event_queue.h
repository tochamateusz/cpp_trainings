#ifndef EVENT_QUEUE
#define EVENT_QUEUE

#include <mutex>
#include <queue>

class EventQueue {
public:
  static EventQueue &instance() {
    static EventQueue instance;
    return instance;
  }

  template <typename F> void post(F &&f) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(std::forward<F>(f));
    condition_.notify_one();
  }

  void run();
  void stop();

private:
  EventQueue() = default;
  std::queue<std::function<void()>> queue_;
  std::mutex mutex_;
  std::condition_variable condition_;
  std::atomic<bool> running_{true};
};

#endif
