cmake_minimum_required(VERSION 3.5)
project(industrialism VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

# library find functions
find_package(Vulkan REQUIRED)

# add external libs (with cmake)
add_subdirectory(lib/glm)
add_subdirectory(lib/glfw)
add_subdirectory(lib/vkb)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/engine.cpp
        src/initializers.cpp
        include/engine.hpp
        include/util.hpp
        include/images.hpp
        src/images.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${Vulkan_INCLUDE_DIRS}
        glm
        glfw
        PRIVATE
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${Vulkan_LIBRARIES}
        glm
        glfw
        vk-bootstrap::vk-bootstrap
        PRIVATE
)