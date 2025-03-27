set(TARGET_SUFFIX domain)
set(TARGET_NAME ${PROJECT_NAME}_${TARGET_SUFFIX})

add_library(${TARGET_NAME} STATIC
    JpegConsumer.hpp
    JpegBuffer.hpp
    JpegBuffer.cpp
    VideoWriter.hpp
    VideoWriter.cpp
)
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

find_package(OpenCV REQUIRED)

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${TARGET_NAME} PUBLIC ${OpenCV_LIBS})
