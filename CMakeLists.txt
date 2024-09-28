cmake_minimum_required(VERSION 3.14)
project(mdefparser VERSION 1.0.0 LANGUAGES CXX)

set(MDEFPARSER_SOURCES "include/mdefparser/impl/mdefparser.cpp")
set(MDEFPARSER_HEADERS "include/mdefparser/mdefparser.h include/mdefparser/mugendef.hpp")

add_library(mdefparser ${MDEFPARSER_SOURCES})
add_library(mdefparser::mdefparser ALIAS mdefparser)

target_compile_features(mdefparser PUBLIC cxx_std_20)

target_include_directories(mdefparser PUBLIC include/)

target_compile_definitions(
  mdefparser
  PUBLIC
  $<$<CONFIG:Debug>:
    _DEBUG
    DEBUG
  >
)

if(MSVC)
  set_property(TARGET mdefparser PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  set_property(TARGET mdefparser PROPERTY MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug>:EditAndContinue>")
  target_compile_options(
    mdefparser
    PUBLIC
    /W4 /arch:AVX /fp:fast /GS /GT /MP /nologo /Oi /Qpar /utf-8
    $<$<CONFIG:Debug>:/JMC /LDd /Ob0 /Od /RTC1>
    $<$<CONFIG:Release>:/GA /GL /Gy /guard:cf- /LD /Os>
  )
  if(CMAKE_CXX_FLAGS MATCHES "/W3")
    STRING (REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  endif(CMAKE_CXX_FLAGS MATCHES "/W3")
  if(CMAKE_CXX_FLAGS MATCHES "/GR")
    STRING(REPLACE "/GR" "/GR-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else(CMAKE_CXX_FLAGS MATCHES "/GR")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
  endif(CMAKE_CXX_FLAGS MATCHES "/GR")
else(MSVC)
  target_compile_options(
    mdefparser
    PUBLIC
    -Wall -Wextra -mavx -mfpmath=sse
    $<$<CONFIG:Debug>:-Og -g>
    $<$<CONFIG:Release>:-s -Ofast -ftree-vectorize -fomit-frame-pointer>
  )
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # for x64
    target_compile_options(mdefparser PUBLIC -m64)
  else(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # for x86
    target_compile_options(mdefparser PUBLIC -m32)
  endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
endif(MSVC)

# Define for header only

add_library(mdefparser_header_only INTERFACE)
add_library(mdefparser::mdefparser_header_only ALIAS mdefparser_header_only)

target_compile_definitions(mdefparser_header_only INTERFACE MDEFPARSER_HEADER_ONLY=1)
target_compile_features(mdefparser_header_only INTERFACE cxx_std_20)

target_include_directories(mdefparser_header_only INTERFACE include/)

if(MSVC)
  target_compile_options(
    mdefparser_header_only
    INTERFACE
    /utf-8
  )
endif(MSVC)

# Define tests

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(MDEFPARSER_TEST_SOURCES test/parse.cpp test/parse_item.cpp)

add_executable(${PROJECT_NAME}-googletest ${MDEFPARSER_TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}-googletest mdefparser)
target_link_libraries(${PROJECT_NAME}-googletest gtest_main)

add_executable(${PROJECT_NAME}_header_only-googletest ${MDEFPARSER_TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_header_only-googletest mdefparser_header_only)
target_link_libraries(${PROJECT_NAME}_header_only-googletest gtest_main)

add_test(NAME test COMMAND ${PROJECT_NAME}-googletest)
add_test(NAME test_header_only COMMAND ${PROJECT_NAME}_header_only-googletest)
enable_testing()

# Copy assets to working dir
add_custom_command(
  TARGET ${PROJECT_NAME}-googletest POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test/assets $<TARGET_FILE_DIR:${PROJECT_NAME}-googletest>/assets
)
add_custom_command(
  TARGET ${PROJECT_NAME}_header_only-googletest POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test/assets $<TARGET_FILE_DIR:${PROJECT_NAME}-googletest>/assets
)
