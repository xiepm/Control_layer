cmake_minimum_required(VERSION 3.20)

project(han VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)

option(HAN_ENABLE_ASAN "Enable AddressSanitizer for Debug builds." OFF)
option(HAN_ENABLE_TESTING "Enable test targets." ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompileOptions)

find_package(Eigen3 REQUIRED CONFIG)
find_package(Boost REQUIRED)
find_package(pinocchio REQUIRED CONFIG)
find_package(benchmark QUIET CONFIG)

add_subdirectory(src/core)
add_subdirectory(src/types)
add_subdirectory(src/model)
add_subdirectory(src/kin)
add_subdirectory(src/dyn)

add_library(han INTERFACE)
target_include_directories(
  han
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(
  han
  INTERFACE
    han_core
    han_types
    han_model
    han_kin
    han_dyn
)
han_configure_target(han)

add_library(han::han ALIAS han)
add_library(han::core ALIAS han_core)
add_library(han::types ALIAS han_types)
add_library(han::model ALIAS han_model)
add_library(han::kin ALIAS han_kin)
add_library(han::dyn ALIAS han_dyn)

add_subdirectory(examples)

if(HAN_ENABLE_TESTING)
  add_subdirectory(tests)
endif()

install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  TARGETS
    han
    han_core
    han_types
    han_model
    han_kin
    han_dyn
  EXPORT hanTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  EXPORT hanTargets
  FILE hanTargets.cmake
  NAMESPACE han::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/han
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/hanConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/hanConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/han"
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/hanConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/hanConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/hanConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/han"
)
