cmake_minimum_required(VERSION 3.14.0)

project(GMDSSuite)

#==============================================================================
#Versionnage du projet

set(GMDS_SUITE_VERSION_MAJOR 0)
set(GMDS_SUITE_VERSION_MINOR 7)
set(GMDS_SUITE_VERSION_PATCH 2)

set(GMDS_VERSION
        ${GMDS_SUITE_VERSION_MAJOR}.${GMDS_SUITE_VERSION_MINOR}.${GMDS_SUITE_VERSION_PATCH})

set(DEFAULT_PLATFORM_NAME ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})

set(PLATFORM_NAME ${DEFAULT_PLATFORM_NAME} CACHE STRING "Platform named used in
the installation directory name")

if(CMAKE_SYSTEM MATCHES Windows)
  add_definitions(-DWIN32)
endif()

#FOR EIGEN
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/gen/)

add_subdirectory(gmds)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gmds/inc)
link_directories(${CMAKE_BINARY_DIR}/gmds/Debug)
