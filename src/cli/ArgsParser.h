#pragma once

#include <algorithm>
#include <string_view>
#include <vector>

namespace adventofcode::cli::args_parser
{

inline std::string_view get_option(const std::vector<std::string_view>& args, std::string_view option_name) {
    if (const auto it = std::ranges::find(args, option_name); it != args.end()) {
        return *(it + 1);
    }
    return "";
}

inline bool has_option(const std::vector<std::string_view>& args, std::string_view option_name) {
    return std::ranges::find(args, option_name) != args.end();
}

} // namespace adventofcode::cli::args_parser