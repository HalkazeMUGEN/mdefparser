cmake_minimum_required(VERSION 3.14)
project(mdefparser_header_only-example VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

# For stand-alone build
# (For example, if you use a git submodule)
if(NOT TARGET mdefparser)
  find_package(mdefparser REQUIRED)
endif()

## Recommended build style
# include(FetchContent)
# FetchContent_Declare(
#   mdefparser
#   GIT_REPOSITORY https://github.com/HalkazeMUGEN/mdefparser.git
#   GIT_TAG v1.0.0  # Choose any version
# )
# FetchContent_MakeAvailable(mdefparser)

target_link_libraries(${PROJECT_NAME} mdefparser::mdefparser_header_only)
