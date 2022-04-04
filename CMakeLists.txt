cmake_minimum_required(VERSION 3.5)
project(blinkt_interface)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -Wpedantic)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wno-psabi)
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

# Export targets.
set(export_targets ${export_targets};blinkt)
export(EXPORT export_blinkt_interface
  FILE "${PROJECT_BINARY_DIR}/export_blinkt_interface.cmake"
  NAMESPACE blinkt_interface::)

# Create the blinkt_interfaceConfig.cmake
set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
configure_file(blinkt_interfaceConfig.cmake.in
  "${PROJECT_BINARY_DIR}/blinkt_interfaceConfig.cmake" @ONLY)

# Create the blinkt_interfaceConfigVersion.cmake
configure_file(blinkt_interfaceConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/blinkt_interfaceConfigVersion.cmake" @ONLY)

# Install the config files.
install(FILES
  "${PROJECT_BINARY_DIR}/blinkt_interfaceConfig.cmake"
  "${PROJECT_BINARY_DIR}/blinkt_interfaceConfigVersion.cmake"
   DESTINATION "share/${PROJECT_NAME}/cmake"
   COMPONENT dev)
install(EXPORT export_blinkt_interface
  DESTINATION "share/${PROJECT_NAME}/cmake"
  FILE export_blinkt_interface.cmake
  NAMESPACE "${PROJECT_NAME}::"
  COMPONENT dev)

