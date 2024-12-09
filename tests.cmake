include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(solution_check
  tests/solution_check.cpp
)
target_link_libraries(solution_check
  PRIVATE
  GTest::gtest_main
  ${PROBLEMS_LIB}
)

target_include_directories(solution_check
  PRIVATE
  src
)

include(GoogleTest)
gtest_discover_tests(solution_check)
