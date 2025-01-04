#pragma once

#include "ArgsParser.h"
#include "SolverFactory.h"
#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include "Result.h"

namespace adventofcode::cli::utils
{

inline std::optional<int> parseNumber(std::string_view str) {
    std::optional<int> number;
    try {
        number = std::stoi(std::string(str));
    } catch (...) {
        return std::nullopt;
    }
    return number;
}

inline std::optional<int> getDay(std::string_view day_str) {
    if (day_str.empty()) {
        std::cerr << "The day should be provided\n";
        return std::nullopt;
    }

    auto day = parseNumber(day_str);
    if (!day || *day < 1 || *day > 25) {
        std::cerr << "The day should be between 1 and 25\n";
        return std::nullopt;
    }
    return day;
}

inline std::optional<Part> getPart(std::string_view part_str) {
    if (part_str.empty()) {
        return std::nullopt;
    }

    if (part_str == "1") {
        return Part::Part1;
    }
    if (part_str == "2") {
        return Part::Part2;
    }
    std::cerr << "The part should be either 1 or 2\n";
    return std::nullopt;
}

inline std::optional<std::string> getTestFilter(const std::vector<std::string_view>& args) {
    std::string filter = "solution_check/DaySolverTest.Part";
    auto day_str = args_parser::get_option(args, "--day");
    auto part_str = args_parser::get_option(args, "--part");
    auto part = getPart(part_str);
    auto day = getDay(day_str);
    if (part) {
        filter += *part == Part::Part1 ? "1" : "2";
    } else {
        filter += "*";
    }
    filter += "/";
    if (day) {
        const auto day_it = std::ranges::find(available_days, *day);
        if (day_it == available_days.end()) {
            std::cerr << "No solver found for day " << *day << "\n";
            return std::nullopt;
        }
        const auto day_idx = std::distance(available_days.begin(), day_it);
        filter += std::to_string(day_idx);
    } else {
        filter += "*";
    }
    return filter;
}

inline void solveDay(int day, std::optional<Part> part) {
    if (!std::ranges::contains(available_days, day)) {
        std::cerr << "No solver found for day " << day << "\n";
        return;
    }

    auto solve_part = [&](Part p) {
        std::cout << "- Part " << (p == Part::Part1 ? "1" : "2") << "\n";
        const auto solver = createSolver(day);
        const auto [result, duration] = solver->timed_solve(p);
        std::cout << "  -> Result: " << streamer{result} << " (in " << duration << " µs)\n";
    };

    std::cout << "# Day " << day << " running...\n";
    // If a specific part was provided just run that part.
    if (part) {
        solve_part(*part);
        return;
    }

    // Otherwise run both parts.
    solve_part(Part::Part1);
    solve_part(Part::Part2);
}

} // namespace adventofcode::cli::utils
