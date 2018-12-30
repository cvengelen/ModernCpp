cmake_minimum_required(VERSION 3.3)

project(test_modern)

# Note: sanitize options switch on optimization
# set(CMAKE_CXX_FLAGS "-g -std=c++14 ${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -DGSL_THROW_ON_CONTRACT_VIOLATION")
set(CMAKE_CXX_FLAGS "-g -std=c++14 ${CMAKE_CXX_FLAGS} -DGSL_THROW_ON_CONTRACT_VIOLATION")

include_directories("~/Projects/C++Workspace/GSL/include")

add_executable(UserDefinedLiteral UserDefinedLiteral.cpp)
add_executable(span span.cpp)
add_executable(undefined undefined.cpp)
add_executable(nullpointer nullpointer.cpp)
add_executable(rvo rvo.cpp)
add_executable(map map.cpp)
add_executable(WordCount WordCount.cpp)
