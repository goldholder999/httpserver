# CMakeList.txt: httpserver에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required (VERSION 3.9)

project ("httpserver")
# set (CMAKE_CXX_STANDARD 11)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # vcpackage
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")

endif()

find_package(Boost REQUIRED system)
find_package(cpprestsdk CONFIG REQUIRED) # populates CPP_REST_INCLUDE_DIR and CPP_REST_LIBRARY

find_path(CPPRESTSDK_INCLUDE_DIR cpprest/filestream.h)
include_directories(${CPPRESTSDK_INCLUDE_DIR})

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (httpserver "httpserver.cpp"  )
target_link_libraries(httpserver  
PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_openssl_internal)

add_executable (httpclient  "httpclient.cpp")
target_link_libraries(httpclient  
PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_openssl_internal)
# PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_openssl_internal)
#target_link_libraries(httpserver  ${CPP_REST_LIBRARY})
# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
