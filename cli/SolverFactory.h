#pragma once

#include "DaySolver.h"
#include "problems/day1.h"

#include <memory>

namespace adventofcode {

inline std::unique_ptr<DaySolver> createSolver(int day) {
    switch (day) {
        case 1: return std::make_unique<Day1>();

        default:
            return nullptr;
    }
}

}
