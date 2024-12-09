#include "DaySolver.h"
#include "cli/ArgsParser.h"
#include "cli/SolverFactory.h"
#include "cli/Utils.h"
#include <gtest/gtest.h>
#include <numeric>

class DaySolverTest : public ::testing::TestWithParam<int> {
protected:
  std::unique_ptr<adventofcode::DaySolver> day_solver;
};

TEST_P(DaySolverTest, Part1) {
  std::cout << "Day " << GetParam() << ", part 1 running...\n";
  day_solver = adventofcode::createSolver(GetParam());
  ASSERT_NE(day_solver, nullptr);
  day_solver->setup_test();
  auto result = day_solver->solve(adventofcode::Part::Part1);
  ASSERT_EQ(result, day_solver->get_test_result(adventofcode::Part::Part1));
}

TEST_P(DaySolverTest, Part2) {
  std::cout << "Day " << GetParam() << ", part 2 running...\n";
  day_solver = adventofcode::createSolver(GetParam());
  ASSERT_NE(day_solver, nullptr);
  day_solver->setup_test();
  auto result = day_solver->solve(adventofcode::Part::Part2);
  ASSERT_EQ(result, day_solver->get_test_result(adventofcode::Part::Part2));
}

INSTANTIATE_TEST_SUITE_P(solution_check, DaySolverTest, ::testing::ValuesIn([] {
                           std::array<int, 25> all_days;
                           std::iota(all_days.begin(), all_days.end(), 1);
                           return all_days;
                         }()));

inline void printUsage() {
  std::cout << "Usage: ./solution_check [--day <number>] [--alldays] [--part 1|2] [--help]\n";
}

int main(int argc, char **argv) {
  using namespace adventofcode;

  testing::InitGoogleTest(&argc, argv);

  // Custom parsing to make the command line more usable.
  const std::vector<std::string_view> args(argv, argv + argc);

  if (cli::args_parser::has_option(args, "--help")) {
    printUsage();
    return 0;
  }

  auto all_days = cli::args_parser::has_option(args, "--alldays");
  if (all_days) {
    return RUN_ALL_TESTS();
  }

  ::testing::GTEST_FLAG(filter) = cli::utils::getTestFilter(args).c_str();
  return RUN_ALL_TESTS();
}