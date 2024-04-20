cmake_minimum_required(VERSION 3.5)
project(industrialism_engine VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

# library find functions
find_package(Vulkan REQUIRED)

# add external libs (with cmake)
add_subdirectory(lib/glm)
add_subdirectory(lib/glfw)

add_library(${PROJECT_NAME} src/engine.cpp
        src/kvc/kvc_window.cpp
        src/kvc/kvc_pipeline.cpp
        src/kvc/kvc_instance.cpp
        src/kvc/kvc_device.cpp
        src/kvc/kvc_surface.cpp
)

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
    PRIVATE
)