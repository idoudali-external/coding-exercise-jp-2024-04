add_executable(app1 app1.cc)

target_include_directories(app1 PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(app1 PRIVATE cpp-template::library)

install(
  TARGETS app1
  # IMPORTANT: Add the app1 executable to the "export-set"
  EXPORT CppTempalteTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
)
