#ifndef CHANNELS
#define CHANNELS

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

template <typename T> class Channel {
public:
  using value_type = T;

  void send(const T &value) {
    std::unique_lock lock(mutex_);
    queue_.push(value);
    cv_.notify_one();
  }

  std::optional<T> try_receive() {
    std::unique_lock lock(mutex_);
    if (queue_.empty())
      return std::nullopt;
    T value = queue_.front();
    queue_.pop();
    return value;
  }

  T receive() {
    std::unique_lock lock(mutex_);
    cv_.wait(lock, [this] { return !queue_.empty(); });
    T value = queue_.front();
    queue_.pop();
    return value;
  }

private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cv_;
};

#endif
