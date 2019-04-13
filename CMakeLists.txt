cmake_minimum_required(VERSION 3.8)
project(learn-opengl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib)

add_custom_target(assets ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/assets)

set(SOURCES
  cube
  texture
  triangle)

foreach(source ${SOURCES})
  add_executable(${source} ${source}.cpp)
  target_link_libraries(${source} PRIVATE util)
endforeach()
