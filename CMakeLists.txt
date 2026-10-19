cmake_minimum_required(VERSION 4.0 FATAL_ERROR)

# Enable std module support for MSVC - MUST be before project()
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

set(CMAKE_CXX_MODULE_STD ON)

project(Portability
	VERSION 0.1.0
	DESCRIPTION "Synodic Template Library"
	LANGUAGES CXX
)

option(BUILD_TESTING "Build the tests verifying library functionality" ON)

# Provide a namespaced alias
add_library(portability STATIC)
add_library(synodic::portability ALIAS portability)

set_target_properties(portability
	PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS NO
)

target_compile_features(portability PUBLIC cxx_std_23)

# Link dependencies
target_link_libraries(portability)

# Public headers (macros that cannot be exported from modules)
target_sources(portability
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
	FILES
	include/portability/macros.h
)

add_subdirectory(
	src
)

# NOTE: For IDE setups that do not use CMake directly, we setup all IDE directories to mimic
# their system directory structure. See https://gitlab.kitware.com/cmake/cmake/-/issues/25992
file(GLOB_RECURSE file_list ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

# Must be called from the target definition directory. Only matched against 'target_sources'
# files (No nested CMakeList.txt, docs, etc).
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${file_list})

if(BUILD_TESTING AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
	# Do not include CTest because it adds targets and integrations we do not want to support
	enable_testing()

	find_package(GTest REQUIRED)

	add_subdirectory(
		tests
	)
endif()

# Installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Generate package config files
write_basic_package_version_file(
	portabilityConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
	tool/cmake/portabilityConfig.cmake.in
	portabilityConfig.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/portability
)

install(TARGETS portability
	EXPORT portabilityTargets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/portability
)

# Export and package configuration
install(EXPORT portabilityTargets
	FILE portabilityTargets.cmake
	NAMESPACE synodic::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/portability
	CXX_MODULES_DIRECTORY cxx-modules
)

install(
	FILES
	${CMAKE_CURRENT_BINARY_DIR}/portabilityConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/portabilityConfigVersion.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/portability
)
