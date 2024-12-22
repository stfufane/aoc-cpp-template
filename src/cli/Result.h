#pragma once
#include <ostream>
#include <variant>

template<class T>
struct streamer {
    const T& val;
};
template<class T> streamer(T) -> streamer<T>;

template<class T>
std::ostream& operator<<(std::ostream& os, streamer<T> s) {
    os << s.val;
    return os;
}

template<class... Ts>
std::ostream& operator<<(std::ostream& os, streamer<std::variant<Ts...>> sv) {
    std::visit([&os](const auto& v) { os << streamer{v}; }, sv.val);
    return os;
}