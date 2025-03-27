set(TARGET_NAME JpegBufferTest)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(${TARGET_NAME} JpegBufferTest.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE ${PROJECT_NAME}::domain GTest::gtest_main GTest::gmock)
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/tests/unit)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
