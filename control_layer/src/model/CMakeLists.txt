add_library(han_model STATIC placeholder.cpp)

target_include_directories(
  han_model
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(
  han_model
  PUBLIC
    han_core
    han_types
  PRIVATE
    pinocchio::pinocchio
)
han_configure_target(han_model)
