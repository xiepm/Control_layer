add_library(han_dyn STATIC placeholder.cpp)

target_include_directories(
  han_dyn
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(
  han_dyn
  PUBLIC
    han_core
    han_types
    han_model
  PRIVATE
    pinocchio::pinocchio
)
han_configure_target(han_dyn)
