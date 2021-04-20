cmake_minimum_required(VERSION 3.5)
project(blinkt_demo)

set(blinkt_demo_MAJOR_VERSION 0)
set(blinkt_demo_MINOR_VERSION 0)
set(blinkt_demo_PATCH_VERSION 0)
set(blinkt_demo_VERSION
  ${blinkt_demo_MAJOR_VERSION}.${blinkt_demo_MINOR_VERSION}.${blinkt_demo_PATCH_VERSION})

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
  if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wno-psabi)
  endif()
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(blinkt_interface REQUIRED)

add_executable(show_one src/show_one.cpp)
target_link_libraries(show_one blinkt_interface::blinkt)

add_executable(all_off src/all_off.cpp)
target_link_libraries(all_off blinkt_interface::blinkt)

add_executable(run src/run.cpp)
target_link_libraries(run blinkt_interface::blinkt)

add_executable(rainbow src/rainbow.cpp)
target_link_libraries(rainbow blinkt_interface::blinkt)

add_executable(brightness src/brightness.cpp)
target_link_libraries(brightness blinkt_interface::blinkt)

# Install targets.
install(TARGETS rainbow brightness show_one all_off run
  EXPORT export_blinkt_demo
  DESTINATION lib/${PROJECT_NAME})

# Export targets
set(export_targets ${export_targets}; rainbow; brightness; show_one; all_off; run)
export(EXPORT export_blinkt_demo
  FILE "${PROJECT_BINARY_DIR}/export_blinkt_demo.cmake"
  NAMESPACE "{$PROJECT_NAME}::")

# Create the blinkt_demoConfig.cmake
set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
configure_file(blinkt_demoConfig.cmake.in
  "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/blinkt_demoConfig.cmake" @ONLY)

# Create the blinkt_demoConfigVersion.cmake
configure_file(blinkt_demoConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/blinkt_demoConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/blinkt_demoConfig.cmake"
  "${PROJECT_BINARY_DIR}/blinkt_demoConfigVersion.cmake"
  DESTINATION "share/${PROJECT_NAME}/cmake" COMPONENT dev)
install(EXPORT export_blinkt_demo
  DESTINATION "share/${PROJECT_NAME}/cmake"
  FILE export_blinkt_demo.cmake
  COMPONENT dev)
