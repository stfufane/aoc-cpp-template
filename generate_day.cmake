# Usage : cmake -D DAY=1 -P generate_day.cmake
if(NOT DEFINED DAY)
    message(FATAL_ERROR "DAY parameter is required")
endif()

set(TEMPLATE_H_FILE "${CMAKE_SOURCE_DIR}/templates/day_template.h.in")
set(OUTPUT_H_FILE "${CMAKE_SOURCE_DIR}/problems/day${DAY}.h")
configure_file(${TEMPLATE_H_FILE} ${OUTPUT_H_FILE} @ONLY)

set(TEMPLATE_CPP_FILE "${CMAKE_SOURCE_DIR}/templates/day_template.cpp.in")
set(OUTPUT_CPP_FILE "${CMAKE_SOURCE_DIR}/problems/day${DAY}.cpp")
configure_file(${TEMPLATE_CPP_FILE} ${OUTPUT_CPP_FILE} @ONLY)

message(STATUS "Generated ${OUTPUT_H_FILE} and ${OUTPUT_CPP_FILE} for day ${DAY}")