cmake_minimum_required(VERSION 3.10)
project(4DShi VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find required packages
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Add source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
)

# Add header files
file(GLOB_RECURSE HEADERS 
    "include/*.h"
    "include/*.hpp"
)

# Create executable
add_executable(4d-shi ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(4d-shi PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${Vulkan_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(4d-shi PRIVATE
    ${Vulkan_LIBRARIES}
    glfw
    glm
)

# Copy shaders to build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Install rules
install(TARGETS 4d-shi
    RUNTIME DESTINATION bin
)

# Enable testing
enable_testing()

# Add compiler warnings
if(MSVC)
    target_compile_options(4d-shi PRIVATE /W4)
else()
    target_compile_options(4d-shi PRIVATE -Wall -Wextra -Wpedantic)
endif() 