function(han_configure_target target_name)
  if(NOT TARGET "${target_name}")
    message(FATAL_ERROR "han_configure_target expects an existing target: ${target_name}")
  endif()

  get_target_property(target_type "${target_name}" TYPE)

  if(target_type STREQUAL "INTERFACE_LIBRARY")
    set(target_scope INTERFACE)
  else()
    set(target_scope PUBLIC)
  endif()

  target_compile_features("${target_name}" ${target_scope} cxx_std_20)

  if(MSVC)
    target_compile_options("${target_name}" ${target_scope} /W4 /WX)
  else()
    target_compile_options(
      "${target_name}"
      ${target_scope}
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:Release>:-DNDEBUG>
    )

    if(HAN_ENABLE_ASAN)
      target_compile_options(
        "${target_name}"
        ${target_scope}
          $<$<CONFIG:Debug>:-fsanitize=address>
          $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
      )
      target_link_options(
        "${target_name}"
        ${target_scope}
          $<$<CONFIG:Debug>:-fsanitize=address>
      )
    endif()
  endif()
endfunction()
