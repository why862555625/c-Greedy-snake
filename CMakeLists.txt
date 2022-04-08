cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)
project(GREEDY-SNAKE)
aux_source_directory(./src DIR_SRC)
add_executable(main ${DIR_SRC})
add_subdirectory(deps/SDL)
target_link_libraries(main PRIVATE
curl
pthread 
SDL2main
SDL2-static
)