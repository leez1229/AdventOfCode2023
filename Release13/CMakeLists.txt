cmake_minimum_required(VERSION 3.0.0)
project("Release_1_Part_1" VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable("Release_1_Part_1" 
main.cpp
FileLineReader.h
FileLineReader.cpp
FileBlockReader.h
FileBlockReader.cpp
Part1.h
Part1.cpp
Part2.h
Part2.cpp
Part3.h
Part3.cpp
HelperFunctions.h
HelperFunctions.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
