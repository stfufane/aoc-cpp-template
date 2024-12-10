#include "cli/ArgsParser.h"
#include "cli/Utils.h"
#include <optional>
#include <vector>

inline void printUsage() { std::cout << "Usage: ./adventofcode [--day <number>] [--alldays] [--part 1|2] [--help]\n"; }

int main(int argc, char** argv) {
    using namespace adventofcode;

    const std::vector<std::string_view> args(argv, argv + argc);

    if (cli::args_parser::has_option(args, "--help")) {
        printUsage();
        return 0;
    }

    if (cli::args_parser::has_option(args, "--alldays") || !cli::args_parser::has_option(args, "--day")) {
        for (int day = 1; day <= 25; ++day) {
            cli::utils::solveDay(day, std::nullopt);
        }
    } else {
        auto day_str = cli::args_parser::get_option(args, "--day");
        if (auto day = cli::utils::getDay(day_str)) {
            auto part_str = cli::args_parser::get_option(args, "--part");
            cli::utils::solveDay(*day, cli::utils::getPart(part_str));
        } else {
            printUsage();
            return 1;
        }
    }

    return 0;
}
