set(TARGET_SUFFIX infrastructure)
set(TARGET_NAME ${PROJECT_NAME}_${TARGET_SUFFIX})

add_library(${TARGET_NAME} STATIC
    VideoReceiver.hpp
    VideoReceiver.cpp
)
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${TARGET_NAME} PUBLIC ${PROJECT_NAME}::domain userver::core)
