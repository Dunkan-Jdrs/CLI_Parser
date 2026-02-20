file(GLOB_RECURSE Sources src/*.cpp)

add_library(Js_CLI_Parser STATIC ${Sources})
target_include_directories(Js_CLI_Parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)