cmake_minimum_required(VERSION 3.10)

project(CTestExampleCrashOnTimeout VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use GTest
enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Set up our test executable
add_executable(my_test tests/test_my_test.cc)
target_link_libraries(my_test gtest gtest_main)

add_test(NAME YourTest COMMAND my_test)
set_tests_properties(YourTest PROPERTIES
  TIMEOUT                      1
  TIMEOUT_SIGNAL_NAME          SIGUSR1
)
