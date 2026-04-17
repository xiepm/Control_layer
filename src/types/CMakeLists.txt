add_library(han_types INTERFACE)

target_include_directories(
  han_types
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(han_types INTERFACE Eigen3::Eigen pinocchio::pinocchio)
han_configure_target(han_types)
