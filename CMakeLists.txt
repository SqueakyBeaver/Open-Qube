cmake_minimum_required(VERSION 3.0.0)
project(Qube-Adventures VERSION 0.1.0)

include(CTest)
enable_testing()
set(GCC_COVERAGE_COMPILE_FLAGS  "-pedantic-errors -Wall -Wextra -Werror -Weffc++ -Werror")
set(GCC_COVERAGE_LINK_FLAGS "-isystem C:/msys64/mingw64/include -isystem C:/msys64/mingw64/include/c++/10.2.0")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(Qube-Adventures Qube-main.cpp Qube.cpp Enemy.cpp HealthBar.cpp)
target_link_libraries(Qube-Adventures sfml-graphics sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
