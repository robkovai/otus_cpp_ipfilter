cmake_minimum_required(VERSION 3.2)

project(otus_cpp_ipfilter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(ip_filter "main.cpp")
add_library(ip_filter_lib "library.cpp")
add_executable(ip_filter_tests "tests.cpp")

set_target_properties(ip_filter ip_filter_lib ip_filter_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")

set_target_properties(ip_filter_tests PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

target_link_libraries(ip_filter
    ip_filter_lib)

target_link_libraries(ip_filter_tests
    ${Boost_LIBRARIES}
    ip_filter_lib)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_CONTACT "dedi4@mail.ru")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)

enable_testing()
add_test(ipfilter_tests ip_filter_tests)
