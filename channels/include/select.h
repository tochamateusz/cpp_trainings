#ifndef SELECT_H
#define SELECT_H

// Select Implementation
#include <optional>
#include <thread>
#include <variant>
template <typename... Channels> class Select {
public:
  using Result = std::variant<typename Channels::value_type...>;

  Select(Channels &...channels) : channels_(channels...) {}

  std::optional<Result> try_select() {
    return std::apply(
        [this](auto &...channels) { return try_select_impl(channels...); },
        channels_);
  }

  Result select() {
    while (true) {
      if (auto result = try_select()) {
        return *result;
      }
      std::this_thread::yield();
    }
  }

private:
  template <typename Channel>
  std::optional<Result> try_channel(Channel &channel) {
    if (auto value = channel.try_receive()) {
      return Result{std::in_place_type_t<typename Channel::value_type>{},
                    *value};
    }
    return std::nullopt;
  }

  template <typename FirstChannel, typename... RestChannels>
  std::optional<Result> try_select_impl(FirstChannel &first,
                                        RestChannels &...rest) {
    if (auto result = try_channel(first)) {
      return result;
    }
    if constexpr (sizeof...(RestChannels) > 0) {
      return try_select_impl(rest...);
    }
    return std::nullopt;
  }

  std::tuple<Channels &...> channels_;
};

#endif // SELECT_H
