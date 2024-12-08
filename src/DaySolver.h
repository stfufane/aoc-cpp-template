#pragma once

#include <string_view>
#include <chrono>
#include "inputs.h"

namespace adventofcode {

enum class Part {
  Part1,
  Part2
};

struct DayResult {
  long result = 0;
  long duration = 0;
};

class DaySolver {
public:
  DaySolver() = delete;
  explicit DaySolver(int inDay) : input_data(inputs[inDay - 1]) {}
  virtual ~DaySolver() = default;

  virtual long solve(Part part, bool is_test) = 0;
  
  DayResult timed_solve(Part part, bool is_test) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = solve(part, is_test);
    auto end = std::chrono::high_resolution_clock::now();
    return {result, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()};
  }

protected:
  std::string_view input_data;
};
} // namespace adventofcode
