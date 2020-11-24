project(roid-rage)
set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 2.8)
aux_source_directory( src/ SRC_LIST )
add_executable(${PROJECT_NAME} ${SRC_LIST})
INCLUDE_DIRECTORIES( /usr/include/allegro5 include/ wykobi/ )
LINK_DIRECTORIES( /usr/lib/x86_64-linux-gnu )
TARGET_LINK_LIBRARIES(roid-rage liballegro.so liballegro_primitives.so liballegro_font.so)

