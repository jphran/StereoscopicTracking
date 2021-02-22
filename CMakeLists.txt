cmake_minimum_required(VERSION 3.10)
project(ZedPlayGround)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/zed/include"
        "/usr/local/cuda/include")
link_directories("/usr/local/zed/lib"
        "/usr/local/cuda/lib64")

add_executable(ZedPlayGround main.cpp)
target_link_libraries(ZedPlayGround sl_zed sl_ai)