#include "button.h"
#include "event_queue.h"
#include <iostream>
#include <thread>

int main(void) {
  std::cout << "\tRun2 Main" << "\n";

  std::thread eventThread([] { EventQueue::instance().run(); });
  Button btn;
  btn.setOnClick([] {
    std::cout << "Button clicked! (Thread: " << std::this_thread::get_id()
              << ")\n";
  });

  std::thread t1([&btn] { btn.click(); });
  std::thread t2([&btn] { btn.click(); });

  t1.join();
  t2.join();

  EventQueue::instance().stop();
  eventThread.join();

  return 0;
}
