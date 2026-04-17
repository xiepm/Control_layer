add_executable(han_smoke 00_smoke.cpp)
target_link_libraries(han_smoke PRIVATE han::han)
han_configure_target(han_smoke)
