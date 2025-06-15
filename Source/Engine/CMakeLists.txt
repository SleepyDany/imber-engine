cmake_minimum_required(VERSION 3.28)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    LIST_DIRECTORIES false
    "${ENGINE_SOURCE_DIR}/*.h"
    "${ENGINE_SOURCE_DIR}/*.cpp"
    "${ENGINE_SOURCE_DIR}/*.inl"
)

add_library(Engine STATIC)

target_sources(Engine
    PUBLIC
    ${SOURCE_FILES}
)

add_library(Imber::Engine ALIAS Engine)
