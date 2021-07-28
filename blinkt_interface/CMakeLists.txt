cmake_minimum_required(VERSION 3.5)
project(blinkt_interface)

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

set(blinkt_interface_MAJOR_VERSION 0)
set(blinkt_interface_MINOR_VERSION 0)
set(blinkt_interface_PATCH_VERSION 0)
set(blinkt_interface_VERSION
  ${blinkt_interface_MAJOR_VERSION}.${blinkt_interface_MINOR_VERSION}.${blinkt_interface_PATCH_VERSION})

add_library(blinkt SHARED src/blinkt.cpp)
target_include_directories(blinkt PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(blinkt PUBLIC gpiodcxx)


# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(blinkt PRIVATE "BLINKT_INTERFACE_BUILDING_LIBRARY")

install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS blinkt
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
# export targets
set(export_targets ${export_targets};blinkt)
export(EXPORT export_blinkt_interface
  FILE "${PROJECT_BINARY_DIR}/export_blinkt_interface.cmake")

# Create the blinkt_interfaceConfig.cmake
set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
configure_file(blinkt_interfaceConfig.cmake.in
  "${PROJECT_BINARY_DIR}/blinkt_interfaceConfig.cmake" @ONLY)

# Create the blinkt_interfaceConfigVersion.cmake
configure_file(blinkt_interfaceConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/blinkt_interfaceConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}/blinkt_interfaceConfig.cmake"
  "${PROJECT_BINARY_DIR}/blinkt_interfaceConfigVersion.cmake"
  DESTINATION "share/${PROJECT_NAME}/cmake" COMPONENT dev)
install(EXPORT export_blinkt_interface
  DESTINATION "share/${PROJECT_NAME}/cmake"
  FILE export_blinkt_interface.cmake
  NAMESPACE "${PROJECT_NAME}::"
  COMPONENT dev)

