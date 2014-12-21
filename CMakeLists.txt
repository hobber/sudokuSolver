cmake_minimum_required(VERSION 2.8)
project(sudokuSolver)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(DEFAULT_FLAGS "-std=c++11 -Wall -Werror -Wno-unused-result")

set(SOURCE_WILDCARDS *.h *.H *.hpp *.hh *.hxx *.c *.C *.cpp *.cc *.cxx)
add_subdirectory(src)
