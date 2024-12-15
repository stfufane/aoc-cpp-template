# Usage : cmake -D DAY=1 -P generate_day.cmake
# or : cmake -D DAYS="1,2,3,4" -P generate_day.cmake
if (NOT DEFINED DAY AND NOT DEFINED DAYS)
    message(FATAL_ERROR "DAY or DAYS parameter is required")
endif()

if (NOT EXISTS "${CMAKE_SOURCE_DIR}/.session")
    message(FATAL_ERROR "Retrieve your cookie from the website and put it in a .session file.")
endif()

function(generate_day day)
    if(NOT "${day}" MATCHES "^[-+]?[0-9]+$")
        message(STATUS "Invalid day number: ${day}")
        return()
    endif()

    message(STATUS "Generate day ${DAY}")
    # Generate the files from the templates
    set(TEMPLATE_H_FILE "${CMAKE_SOURCE_DIR}/templates/day_template.h.in")
    set(TEMPLATE_CPP_FILE "${CMAKE_SOURCE_DIR}/templates/day_template.cpp.in")
    set(OUTPUT_H_FILE "${CMAKE_SOURCE_DIR}/src/problems/day${DAY}.h")
    set(OUTPUT_CPP_FILE "${CMAKE_SOURCE_DIR}/src/problems/day${DAY}.cpp")
    if (EXISTS ${OUTPUT_H_FILE} OR EXISTS ${OUTPUT_CPP_FILE})
        message(STATUS "This day source has already been generated")
    else()
        message(STATUS "Generating source files for day ${DAY}")
        configure_file(${TEMPLATE_H_FILE} ${OUTPUT_H_FILE} @ONLY)
        configure_file(${TEMPLATE_CPP_FILE} ${OUTPUT_CPP_FILE} @ONLY)
    endif()

    # Download the input file from the AoC website
    message(STATUS "Downloading the input...")
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

    message(STATUS "Generated ${OUTPUT_H_FILE} and ${OUTPUT_CPP_FILE} for day ${DAY}")
    message(STATUS "Downloaded input from ${INPUT_URL} to ${OUTPUT_FILE}")
endfunction()


if (DEFINED DAY)
    generate_day(${DAY})
else()
    # Split the DAYS string into a list
    set(DAYS_LIST)
    set(input "${DAYS}")
    while(input MATCHES "([^,]+),?(.*)")
        list(APPEND DAYS_LIST "${CMAKE_MATCH_1}")
        set(input "${CMAKE_MATCH_2}")
    endwhile()

    foreach(DAY IN LISTS DAYS_LIST)
        generate_day(${DAY})
    endforeach()
endif()