add_subdirectory(domain)
add_subdirectory(infrastructure)

add_executable(${PROJECT_NAME} Main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}::infrastructure)
