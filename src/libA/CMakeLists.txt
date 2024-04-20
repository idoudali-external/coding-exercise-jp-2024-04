# Create an object library
add_library(libA_obj OBJECT libA.cc)

set_target_properties(libA_obj PROPERTIES POSITION_INDEPENDENT_CODE 1)
target_include_directories(libA_obj PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(
  libA_obj PROPERTIES PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/libA/libA.h"
)

# Example of a static library
add_library(A STATIC $<TARGET_OBJECTS:libA_obj>)

set_target_properties(
  A PROPERTIES PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/libA/libA.h"
)

install(
  TARGETS A
  EXPORT CppTemplateTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/CppTemplate/libA"
)

# Example of a shared library

add_library(A_shared SHARED $<TARGET_OBJECTS:libA_obj>)
add_library(cpp-template::library ALIAS A_shared)

set_target_properties(
  A_shared PROPERTIES PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/libA/libA.h"
)

install(
  TARGETS A_shared
  EXPORT CppTemplateTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/CppTemplate/libA"
  INCLUDES
  DESTINATION include
)
