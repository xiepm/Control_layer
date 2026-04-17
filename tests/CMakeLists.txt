include(GoogleTest)

find_package(GTest QUIET CONFIG)

set(han_test_layers core types model kin dyn)

foreach(layer IN LISTS han_test_layers)
  add_custom_target("han_${layer}_tests")
endforeach()

if(GTest_FOUND)
  message(STATUS "GTest found. Add test sources under tests/<layer>/test_*.cpp to populate targets.")
else()
  message(STATUS "GTest not found. Layer test targets remain as placeholders for the project skeleton.")
endif()
