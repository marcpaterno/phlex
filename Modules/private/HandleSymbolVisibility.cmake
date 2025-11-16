include(GenerateExportHeader)

function(phlex_handle_symbol_visibility target)
  set(EXPORT_HEADER "${CMAKE_CURRENT_BINARY_DIR}/include/${target}_export.hpp")
  set(EXPORT_MACRO_NAME "${target}_EXPORT")

  generate_export_header(${target}
    BASE_NAME ${target}
    EXPORT_FILE_NAME ${EXPORT_HEADER}
    EXPORT_MACRO_NAME ${EXPORT_MACRO_NAME}
    STATIC_DEFINE "${target}_STATIC_DEFINE"
  )

  target_include_directories(${target}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<INSTALL_INTERFACE:include>
  )

endfunction()
