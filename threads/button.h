#ifndef BUTTON
#define BUTTON

#include "event_queue.h"
#include <functional>

class Button {
public:
  using Callback = std::function<void()>;
  void setOnClick(Callback callback);

  // Simulate button click (can be called from any thread)
  void click();

private:
  Callback onClick_;
};

#endif
