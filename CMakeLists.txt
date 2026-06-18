cmake_minimum_required(VERSION 3.20)

project(LodevRaycaster LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL REQUIRED)

add_executable(LodevRaycaster
    main.cpp
    quickcg.cpp
)

target_link_libraries(LodevRaycaster PRIVATE SDL::SDL)