#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include "SolverFactory.h"

namespace adventofcode::utils
{

inline void printUsage() {
  std::cout << "Usage: ./adventofcode [--day <number>] [--alldays] [--test]\n";
}

inline std::optional<int> getDay(std::string_view day_str) {
  std::optional<int> day;
  if (day_str.empty()) {
    std::cerr << "Day number not provided\n";
    printUsage();
    return 1;
  }
  
  try {
    day = std::stoi(std::string(day_str));
  } catch (...) {
    std::cerr << "Invalid day number\n";
    printUsage();
    return std::nullopt;
  }

  if (!day || *day < 1 || *day > 25) {
    std::cerr << "The day should be between 1 and 25\n";
    printUsage();
    return std::nullopt;
  }
  return day;
}

inline void solveDay(int day, bool is_test) {
  auto solver = adventofcode::createSolver(day);
  if (!solver) {
    std::cerr << "No solver found for day " << day << "\n";
    return;
  }

  auto solve_part = [&](adventofcode::Part part) {
    std::cout << "- Part " << (part == adventofcode::Part::Part1 ? "1" : "2") << "\n";
    auto result = solver->timed_solve(part, is_test);
    std::cout << "  -> Result: " << result.result << " (in " <<  result.duration << " µs)\n";
  };

  std::cout << "# Day " << day << " running...\n";
  solve_part(adventofcode::Part::Part1);
  solve_part(adventofcode::Part::Part2);
}

}