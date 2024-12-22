cmake_minimum_required(VERSION 3.20)
project(adventofcode
        VERSION 0.1.0
        DESCRIPTION "Advent of Code 2024"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
if(MSVC)
        add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
        set(CMAKE_CXX_FLAGS "-Wshadow -Wall -Wextra -Wfatal-errors -Wconversion -Wpedantic")
        set(CMAKE_CXX_FLAGS_DEBUG "-g")
        set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

### INPUTS ###
### Handle inputs as string_views and auto generate inputs.h
set(INPUTS_CONTENT "")
foreach(DAY_NUMBER RANGE 1 25)
        if (EXISTS "${CMAKE_SOURCE_DIR}/inputs/day${DAY_NUMBER}.txt")
                file(READ "${CMAKE_SOURCE_DIR}/inputs/day${DAY_NUMBER}.txt" INPUT_CONTENT)
                # Remove the line break at the end of the file or the split_view will return one extra line
                string(REGEX REPLACE "\n$" "" TRIMMED_INPUT_CONTENT "${INPUT_CONTENT}")
                string(APPEND INPUTS_CONTENT "R\"(${TRIMMED_INPUT_CONTENT})\",\n")
        else()
                string(APPEND INPUTS_CONTENT "R\"()\",\n")
        endif()
endforeach()

configure_file(
        ${CMAKE_SOURCE_DIR}/templates/inputs.h.in
        ${CMAKE_SOURCE_DIR}/src/inputs.h
        @ONLY
)
### END INPUTS ###

### DAY SOLVERS ###
### Append the day solvers to the factory
file(GLOB DAY_SOLVERS "${CMAKE_SOURCE_DIR}/src/problems/day*.h")
list(LENGTH DAY_SOLVERS NB_DAYS)
set(CASES "")
set(INCLUDES "")
set(AVAILABLE_DAYS "")

foreach(DAY_SOLVER ${DAY_SOLVERS})
        get_filename_component(DAY ${DAY_SOLVER} NAME_WE)
        string(SUBSTRING ${DAY} 3 -1 DAY_NUMBER)
        string(APPEND INCLUDES "#include \"problems/${DAY}.h\"\n")
        string(APPEND CASES "        case ${DAY_NUMBER}: return std::make_unique<Day${DAY_NUMBER}>();\n")
        string(APPEND AVAILABLE_DAYS "${DAY_NUMBER}, ")
endforeach()

configure_file(
        ${CMAKE_SOURCE_DIR}/templates/SolverFactory.h.in
        ${CMAKE_SOURCE_DIR}/src/cli/SolverFactory.h
        @ONLY
)
### END DAY SOLVERS ###

# Watch for changes in inputs and problems so it reconfigures at build automatically
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/inputs)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/problems)

# Create a library containing all the problems
set(PROBLEMS_LIB problems)
file (GLOB PROBLEMS "${CMAKE_SOURCE_DIR}/src/problems/*")
add_library(${PROBLEMS_LIB} STATIC ${PROBLEMS})
set_target_properties(${PROBLEMS_LIB} PROPERTIES LINKER_LANGUAGE CXX)

# Generate the final executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROBLEMS_LIB})

target_include_directories(${PROJECT_NAME} PRIVATE src)

# Add tests
include(tests.cmake)