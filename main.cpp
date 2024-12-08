#include "src/ArgsParser.h"
#include "src/Utils.h"
#include <vector>

int main(int argc, char **argv) {
  using namespace adventofcode;

  const std::vector<std::string_view> args(argv, argv + argc);

  auto is_test = args_parser::has_option(args, "--test");
  auto all_days = args_parser::has_option(args, "--alldays");

  if (all_days) {
    for (int i = 1; i <= 25; ++i) {
      utils::solveDay(i, is_test);
    }
  } else {
    auto day_str = args_parser::get_option(args, "--day");
    if (auto day = utils::getDay(day_str)) {
      utils::solveDay(*day, is_test);
    }
  }

  return 0;
}
