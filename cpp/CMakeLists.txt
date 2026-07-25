cmake_minimum_required(VERSION 3.31.6)

project(dirtBreaker)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRECTORIES})

add_executable(${PROJECT_NAME} src/main.cpp src/getBufferFileDescriptor.cpp src/getVideoDevices.cpp src/scale565MatrixTo565Array.cpp src/getDevicePath.cpp src/visibleCamLoop.cpp src/capture.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
