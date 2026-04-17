add_library(han_core STATIC placeholder.cpp)

target_include_directories(
  han_core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(han_core PUBLIC Eigen3::Eigen Boost::boost)
han_configure_target(han_core)
