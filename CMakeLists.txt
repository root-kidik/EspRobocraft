cmake_minimum_required(VERSION 3.12...3.31)
project(esp_robocraft CXX)

find_package(userver COMPONENTS core REQUIRED)

userver_setup_environment()

add_library(${PROJECT_NAME}_objs OBJECT
    src/video.hpp
    src/video.cpp
)

find_package(OpenCV REQUIRED)

target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver::core ${OpenCV_LIBS})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)

userver_testsuite_add_simple()
