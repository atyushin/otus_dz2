cmake_minimum_required(VERSION 3.10)

project(ipFilter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(
version.h.in
${CMAKE_CURRENT_SOURCE_DIR}/version.h
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ip_filter-12995-758870.tsv ${CMAKE_CURRENT_BINARY_DIR}/ip_filter-12995-758870.tsv COPYONLY)

set (SOURCES 
main.cpp
)

set (HEADERS 
version.h
)

add_executable(ipFilter ${SOURCES} ${HEADERS})

#set_target_properties( ipFilter PROPERTIES 
#CXX_STANDART 11
#CXX_STANDART 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=c++14")

install(TARGETS ipFilter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT blinkers@mail.ru)

include(CPack)

