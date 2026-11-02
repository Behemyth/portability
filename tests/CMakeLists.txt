cmake_minimum_required(VERSION 4.5 FATAL_ERROR)

project(tests
	DESCRIPTION "Test project for the Portability library"
	LANGUAGES CXX
)

add_executable(tests)

set_target_properties(tests
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS NO
)

target_link_libraries(tests
	PRIVATE
	synodic::portability
	GTest::gtest
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

add_subdirectory(
	unit
)
