cmake_minimum_required(VERSION 3.10)
project(aeda1718_ci3)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(aeda1718_ci3 main.cpp Tests/Test.cpp Tests/Expertize.cpp Tests/Student.cpp Tests/Project.cpp Tests/FEUPConsulting.cpp)

target_link_libraries(aeda1718_ci3 gtest gtest_main)
