# Example tests
add_executable(example_test example_test.cc)

target_include_directories(example_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(example_test PRIVATE gtest::gtest)
target_link_libraries(example_test gtest::gtest)
target_link_libraries(example_test gtest_main cpp-template::library)

include(GoogleTest)
gtest_discover_tests(example_test)
