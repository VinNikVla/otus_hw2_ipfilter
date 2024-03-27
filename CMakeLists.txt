cmake_minimum_required(VERSION 3.16)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

option(WITH_GOOGLE_TEST "Whether to build Google test" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter ip_filter.cpp)
add_library(ipaddr  ipv4_address.h ipv4_address.cpp utilities.h)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ipaddr
)

if(WITH_GOOGLE_TEST)

find_package(GTest REQUIRED)
enable_testing()

add_executable(test_ipaddress test_ipv4_address.cpp)

set_target_properties(test_ipaddress PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(test_ipaddress
GTest::gtest_main
    ipaddr
)

gtest_discover_tests(test_ipaddress)

    # find_program(SH_PROG sh REQUIRED)
    # find_program(MD5_PROG md5sum REQUIRED)
    # add_test(testmd5 ${SH_PROG} -c "[ \"24e7a7b2270daee89c64d3ca5fb3da1a  -\" = \"$(./ip_filter < ${CMAKE_SOURCE_DIR}/ip_filter.tsv | ${MD5_PROG})\" ]")
endif()


if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)