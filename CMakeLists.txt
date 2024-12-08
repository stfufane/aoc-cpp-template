cmake_minimum_required(VERSION 3.20)
project(adventofcode
        VERSION 0.1.0
        DESCRIPTION "Advent of Code 2024"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(src problems)

### INPUTS ###
### Handle inputs as string_views and auto generate inputs.h
set(INPUTS_CONTENT "")
string(APPEND INPUTS_CONTENT "inline constexpr std::array<std::string_view, 25> inputs = {\n")
foreach(DAY_NUMBER RANGE 1 25)
        if (EXISTS "${CMAKE_SOURCE_DIR}/inputs/day${DAY_NUMBER}.txt")
                file(READ "${CMAKE_SOURCE_DIR}/inputs/day${DAY_NUMBER}.txt" INPUT_CONTENT)
                string(APPEND INPUTS_CONTENT "R\"(${INPUT_CONTENT})\",\n")
        else()
                string(APPEND INPUTS_CONTENT "R\"()\",\n")
        endif()
endforeach()
string(APPEND INPUTS_CONTENT "};\n")

configure_file(
        ${CMAKE_SOURCE_DIR}/templates/inputs.h.in
        ${CMAKE_SOURCE_DIR}/src/inputs.h
        @ONLY
)
### END INPUTS ###

### DAY SOLVERS ###
### Append the day solvers to the factory
file(GLOB DAY_SOLVERS "${CMAKE_SOURCE_DIR}/problems/day*.h")
set(CASES "")
set(INCLUDES "")

foreach(DAY_SOLVER ${DAY_SOLVERS})
        get_filename_component(DAY ${DAY_SOLVER} NAME_WE)
        string(SUBSTRING ${DAY} 3 -1 DAY_NUMBER)
        string(APPEND INCLUDES "#include \"../problems/${DAY}.h\"\n")
        string(APPEND CASES "        case ${DAY_NUMBER}: return std::make_unique<Day${DAY_NUMBER}>();\n")
endforeach()

configure_file(
        ${CMAKE_SOURCE_DIR}/templates/SolverFactory.h.in
        ${CMAKE_SOURCE_DIR}/src/SolverFactory.h
        @ONLY
)
### END DAY SOLVERS ###

# Watch for changes in inputs and problems so it reconfigures at build automatically
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/inputs)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/problems)

# Generate the final executable
file (GLOB PROBLEMS "${CMAKE_SOURCE_DIR}/problems/*")
add_executable(${PROJECT_NAME} main.cpp
        ${PROBLEMS}
)
