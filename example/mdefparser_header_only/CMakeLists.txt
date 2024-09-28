cmake_minimum_required(VERSION 3.14)
project(mdefparser_header_only-example VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

include(FetchContent)
FetchContent_Declare(
  mdefparser
  GIT_REPOSITORY https://github.com/HalkazeMUGEN/mdefparser.git
  GIT_TAG main  # Choose any version
)
FetchContent_MakeAvailable(mdefparser)

target_link_libraries(${PROJECT_NAME} mdefparser_header_only)
