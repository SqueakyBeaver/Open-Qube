cmake_minimum_required(VERSION 3.0.0)
project(Qube-Defense VERSION 0.0.2)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(Qube-Defense Qube-main.cpp Qube.cpp Enemy.cpp HealthBar.cpp Application.cpp)
target_link_libraries(Qube-Defense sfml-graphics sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
