#include "button.h"

void Button::setOnClick(Callback callback) { onClick_ = callback; }

void Button::click() {
  if (onClick_) {
    EventQueue::instance().post([this] { onClick_(); });
  }
}
