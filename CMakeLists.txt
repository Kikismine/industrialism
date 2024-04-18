cmake_minimum_required(VERSION 3.5)
project(industrialism VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(engine)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} industrialism_engine)
target_link_directories(${PROJECT_NAME} PRIVATE industrialism_engine)