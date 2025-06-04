#
# Lines inspired by https://google.github.io/googletest/quickstart-cmake.html
#

# Note: include(GoogleTest)and enable_testing() already done in top CMakeLists.txt

add_executable(unitTests
        RoundTargetTest.cpp
)
target_include_directories(unitTests
        PRIVATE
        ../Include
)
target_link_libraries(unitTests GTest::gtest_main lib_simpleGame sfml-graphics)
if (WIN32)
  target_link_libraries(unitTests wsock32.lib ws2_32.lib)
else() # We are under UNIX
    target_link_options(unitTests PRIVATE -pthread)
endif()

# The next line enables CMake’s test runner to discover the tests included in the binary,
# using the GoogleTest CMake module (which was included in root CMakeLists.txt).
include(GoogleTest)
gtest_discover_tests(unitTests)