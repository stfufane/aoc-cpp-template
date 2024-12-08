#include "src/SolverFactory.h"
#include "src/ArgsParser.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

void printUsage() {
  std::cout << "Usage: ./adventofcode [--day <number>] [--alldays] [--test]\n";
}

std::optional<int> getDay(const std::vector<std::string_view>& args) {
  std::optional<int> day;
  auto day_str = adventofcode::args_parser::get_option(args, "--day");
  if (day_str.empty()) {
    printUsage();
    return 1;
  }
  
  try {
    day = std::stoi(std::string(day_str));
  } catch (...) {
    return std::nullopt;
  }

  if (!day || *day < 1 || *day > 25) {
    printUsage();
    return 1;
  }
  return day;
}

int main(int argc, char **argv) {
  const std::vector<std::string_view> args(argv, argv + argc);

  auto is_test = adventofcode::args_parser::has_option(args, "--test");
  auto day = getDay(args);

  auto solver = adventofcode::createSolver(*day);
  if (!solver) {
    std::cerr << "No solver found for day " << *day << "\n";
    return 1;
  }

  auto solve_part = [&](adventofcode::Part part) {
    std::cout << "Part " << (part == adventofcode::Part::Part1 ? "1" : "2") << " running...\n";
    auto result = solver->timed_solve(part, is_test);
    std::cout << "Result: " << result.result << " (in " <<  result.duration << " µs)\n";
  };

  solve_part(adventofcode::Part::Part1);
  solve_part(adventofcode::Part::Part2);

  return 0;
}
