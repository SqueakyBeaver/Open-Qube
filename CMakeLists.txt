cmake_minimum_required(VERSION 3.0.0)
project(Open-Qube VERSION 0.0.2)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX /Wall /std:c++20)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror -std=c++20)
endif()

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(Open-Qube
               src/main.cpp
               src/Qube.hpp
               src/Enemy.hpp
               src/HealthBar.hpp
               src/Application.hpp
               src/Entity.hpp
               src/EnemyGroup.hpp
               src/RandGen.hpp)

target_link_libraries(Open-Qube sfml-graphics sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
