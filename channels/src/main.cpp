#include "../include/channels.h"
#include "../include/select.h"
#include <iostream>
#include <ostream>
#include <thread>

struct Event {
  std::string type;
};

std::mutex io_mutex;
std::atomic<bool> running(true);

int main(void) {
  Channel<int> int_channel;
  Channel<std::string> string_channel;
  Channel<double> double_channel;
  Channel<Event> event_channel;

  // Producer thread
  // std::thread producer([&] {
  //   while (true) {
  //     int_channel.send(42);
  //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
  //   }
  // });

  // std::thread producer2([&] {
  //   while (true) {
  //     string_channel.send("test");
  //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //   }
  // });
  //
  std::thread input_th([&] {
    std::string input;

    // Initial prompt
    {
      std::lock_guard<std::mutex> lock(io_mutex);
      std::cout << "Enter command (or 'quit' to exit): " << std::flush;
    }

    while (running) {
      if (std::getline(std::cin, input)) { // Check if getline succeeded
        {
          std::lock_guard<std::mutex> lock(io_mutex);
          event_channel.send(Event{.type = input});
        }

        if (input == "quit") {
          running = false;
          break;
        }

        // Prompt for next input
        {
          std::lock_guard<std::mutex> lock(io_mutex);
          std::cout << "Enter command (or 'quit' to exit): \n" << std::flush;
        }
      } else {
        // Handle input error
        running = false;
        break;
      }
    }
  });

  std::thread consumer([&] {
    Select select{int_channel, string_channel, double_channel, event_channel};
    while (true) {
      auto result = select.select();

      std::visit(
          [](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) {
              std::cout << "Received int: " << arg << "\n";
            } else if constexpr (std::is_same_v<T, std::string>) {
              std::cout << "Received string: " << arg << "\n";
            } else if constexpr (std::is_same_v<T, double>) {
              std::cout << "Received double: " << arg << "\n";
            } else if constexpr (std::is_same_v<T, Event>) {
              std::cout << "Received event: " << arg.type << "\n";
            }
          },
          result);
    }
  });

  int counter = 0;
  while (running) {
    {
      std::lock_guard<std::mutex> lock(io_mutex);
      std::cout << "Working... " << counter++ << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // producer.join();
  // producer2.join();
  // producer3.join();
  input_th.join();
  consumer.join();

  return 0;
}
