cmake_minimum_required(VERSION 3.15)
project(CppTemplate)

set(CMAKE_CXX_STANDARD 14)

set(CPPTEMPLATE_MAJOR_VERSION 0)
set(CPPTEMPLATE_MINOR_VERSION 1)
set(CPPTEMPLATE_PATCH_VERSION 0)
set(CPPTEMPLATE_VERSION
    ${CPPTEMPLATE_MAJOR_VERSION}.${CPPTEMPLATE_MINOR_VERSION}.${CPPTEMPLATE_PATCH_VERSION}
)

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR
    lib
    CACHE PATH "Installation directory for libraries"
)
set(INSTALL_BIN_DIR
    bin
    CACHE PATH "Installation directory for executables"
)
set(INSTALL_INCLUDE_DIR
    include
    CACHE PATH "Installation directory for header files"
)
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/CppTemplate)
endif()
set(INSTALL_CMAKE_DIR
    ${DEF_INSTALL_CMAKE_DIR}
    CACHE PATH "Installation directory for CMake files"
)

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Helper configuration file that holds the values of a number of configuration
# option
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/config.cmake)
  include(${CMAKE_CURRENT_BINARY_DIR}/config.cmake)
else()
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/config.cmake)
  endif()
endif()

find_package(GTest REQUIRED)

# Enable ctest in this project
enable_testing()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)

# Create a custom CMake Package that we can install and use find_package to
# retrive its information Reference
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-to-create-a-ProjectConfig.cmake-file

# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
export(TARGETS A A_shared app1
       FILE "${PROJECT_BINARY_DIR}/CppTemplateTargets.cmake"
)

# Export the package for use from the build-tree (this registers the build-tree
# with a global CMake-registry)
export(PACKAGE CppTemplate)

# Create the CppTemplateConfig.cmake and CppTemplateConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
     "${INSTALL_INCLUDE_DIR}"
)
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(
  CppTemplateConfig.cmake.in "${PROJECT_BINARY_DIR}/CppTemplateConfig.cmake"
  @ONLY
)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${CppTemplate_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(
  CppTemplateConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CppTemplateConfig.cmake" @ONLY
)
# ... for both
configure_file(
  CppTemplateConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/CppTemplateConfigVersion.cmake" @ONLY
)

# Install the CppTemplateConfig.cmake and CppTemplateConfigVersion.cmake
install(
  FILES "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CppTemplateConfig.cmake"
        "${PROJECT_BINARY_DIR}/CppTemplateConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}"
  COMPONENT dev
)

# Install the export set for use with the install-tree
install(
  EXPORT CppTemplateTargets
  DESTINATION "${INSTALL_CMAKE_DIR}"
  COMPONENT dev
)
