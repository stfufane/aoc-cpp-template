#pragma once

#include <string_view>
#include <vector>
#include <algorithm>

namespace adventofcode::args_parser {

inline std::string_view get_option(const std::vector<std::string_view>& args, std::string_view option_name) {
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == option_name)
      if (it + 1 != end)
        return *(it + 1);
  }
  return "";
}

inline bool has_option(const std::vector<std::string_view>& args, std::string_view option_name) {
    return std::find(args.begin(), args.end(), option_name) != args.end();
}

} // namespace adventofcode::args_parser