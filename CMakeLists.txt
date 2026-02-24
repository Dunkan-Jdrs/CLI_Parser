cmake_minimum_required(VERSION 3.14)
project(Js_CLI_Parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

add_subdirectory(Js_CLI_Parser)
add_subdirectory(Js_CLI_Parser_Tests)