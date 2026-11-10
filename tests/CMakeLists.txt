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

if(CMAKE_CONFIGURATION_TYPES)
	set(_test_is_multi_config ON)
else()
	set(_test_is_multi_config OFF)
endif()
add_test(
	NAME test_package_consumer
	COMMAND ${CMAKE_COMMAND}
		"-DTEST_PROJECT_BINARY_DIR=${CMAKE_BINARY_DIR}"
		"-DTEST_SOURCE_DIR=${CMAKE_SOURCE_DIR}/test_package"
		"-DTEST_GENERATOR=${CMAKE_GENERATOR}"
		"-DTEST_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM}"
		"-DTEST_GENERATOR_TOOLSET=${CMAKE_GENERATOR_TOOLSET}"
		"-DTEST_CONFIG=$<CONFIG>"
		"-DTEST_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
		"-DTEST_IS_MULTI_CONFIG=${_test_is_multi_config}"
		"-DTEST_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
		"-DTEST_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}"
		"-DTEST_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
		"-DTEST_CXX_FLAGS=${CMAKE_CXX_FLAGS}"
		"-DTEST_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS}"
		"-DTEST_CXX_STDLIB_MODULES_JSON=${CMAKE_CXX_STDLIB_MODULES_JSON}"
		-P "${CMAKE_CURRENT_LIST_DIR}/test_package.cmake"
)
