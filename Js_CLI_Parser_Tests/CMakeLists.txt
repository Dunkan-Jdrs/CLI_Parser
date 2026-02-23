cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Js_CLI_Parser_Tests
  ${SOURCES})

target_include_directories(Js_CLI_Parser_Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Js_CLI_Parser_Tests PRIVATE
  Js_CLI_Parser
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Js_CLI_Parser_Tests)
