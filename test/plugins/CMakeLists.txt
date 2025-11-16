add_library(module MODULE module.cpp)
set_target_properties(module PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)
target_link_libraries(module PRIVATE phlex::module)

add_library(output MODULE output.cpp)
set_target_properties(output PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)
target_link_libraries(output PRIVATE phlex::module)

add_library(source MODULE source.cpp)
set_target_properties(source PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)
target_link_libraries(source PRIVATE Boost::json phlex::core)

add_test(NAME job:add COMMAND phlex -c ${CMAKE_CURRENT_SOURCE_DIR}/add.jsonnet)

set_tests_properties(
  job:add PROPERTIES ENVIRONMENT SPDLOG_LEVEL=debug ENVIRONMENT
                     PHLEX_PLUGIN_PATH=${CMAKE_CURRENT_BINARY_DIR}
  )
