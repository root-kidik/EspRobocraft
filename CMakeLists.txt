cmake_minimum_required(VERSION 3.12...3.31)

project(esp_robocraft CXX)

find_package(userver COMPONENTS core REQUIRED)

userver_setup_environment()

add_subdirectory(src)

userver_testsuite_add_simple()

add_subdirectory(tests/unit)
