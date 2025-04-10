cmake_minimum_required(VERSION 3.12...3.31)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(esp_robocraft CXX)

find_package(userver COMPONENTS core REQUIRED)

userver_setup_environment()

add_subdirectory(src)

userver_testsuite_add(
  SERVICE_TARGET ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
  PYTHON_BINARY ${TESTSUITE_PYTHON_BINARY}
  PYTEST_ARGS
  --service-config=${CMAKE_SOURCE_DIR}/configs/static_config.yaml
  --service-binary=${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}
  --service-config-vars=${CMAKE_SOURCE_DIR}/configs/config_vars.testing.yaml
)

add_subdirectory(tests/unit)
