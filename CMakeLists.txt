cmake_minimum_required(VERSION 2.8)
project(Q C)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_C_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")

#add_library(ql src/q.c)
add_executable(q src/main.c src/q.c)
target_link_libraries(q m)
