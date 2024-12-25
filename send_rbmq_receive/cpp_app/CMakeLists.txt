cmake_minimum_required(VERSION 3.10)
project(CPPApp)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBRABBITMQ REQUIRED librabbitmq)

add_executable(cpp_app main.cpp)
target_include_directories(cpp_app PRIVATE ${LIBRABBITMQ_INCLUDE_DIRS})
target_link_libraries(cpp_app PRIVATE ${LIBRABBITMQ_LIBRARIES})