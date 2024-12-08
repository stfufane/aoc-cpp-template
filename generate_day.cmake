# Usage : cmake -D DAY=1 -P generate_day.cmake
if (NOT DEFINED DAY)
    message(FATAL_ERROR "DAY parameter is required")
endif()

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/.session")
    message(FATAL_ERROR "Retrieve your cookie from the website and put it in a .session file.")
endif()

# Generate the files from the templates
set(TEMPLATE_H_FILE "${CMAKE_SOURCE_DIR}/templates/day_template.h.in")
set(TEMPLATE_CPP_FILE "${CMAKE_SOURCE_DIR}/templates/day_template.cpp.in")
set(OUTPUT_H_FILE "${CMAKE_SOURCE_DIR}/problems/day${DAY}.h")
set(OUTPUT_CPP_FILE "${CMAKE_SOURCE_DIR}/problems/day${DAY}.cpp")
if (EXISTS ${OUTPUT_H_FILE} OR EXISTS ${OUTPUT_CPP_FILE})
    message(FATAL_ERROR "This day has already been generated")
endif()

# Download the input file from the AoC website
file(READ ${CMAKE_SOURCE_DIR}/.session SESSION_COOKIE)
set(INPUT_URL "https://adventofcode.com/2024/day/${DAY}/input")
set(HEADER "Cookie: session=${SESSION_COOKIE}")
set(OUTPUT_FILE "${CMAKE_SOURCE_DIR}/inputs/day${DAY}.txt")
file(DOWNLOAD ${INPUT_URL} ${OUTPUT_FILE} 
    HTTPHEADER ${HEADER}
    STATUS DOWNLOAD_STATUS)
list(GET DOWNLOAD_STATUS 0 DOWNLOAD_RESULT)
if (NOT DOWNLOAD_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to download file from ${INPUT_URL}")
endif()

configure_file(${TEMPLATE_H_FILE} ${OUTPUT_H_FILE} @ONLY)
configure_file(${TEMPLATE_CPP_FILE} ${OUTPUT_CPP_FILE} @ONLY)

message(STATUS "Generated ${OUTPUT_H_FILE} and ${OUTPUT_CPP_FILE} for day ${DAY}")
message(STATUS "Downloaded input from ${INPUT_URL} to ${OUTPUT_FILE}")