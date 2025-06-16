cmake_minimum_required(VERSION 3.28)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/)

file(GLOB_RECURSE MODULE_FILES CONFIGURE_DEPENDS
    LIST_DIRECTORIES true
    "${ENGINE_SOURCE_DIR}/*.h"
    "${ENGINE_SOURCE_DIR}/*.cpp"
    "${ENGINE_SOURCE_DIR}/*.inl"
)

set(MODULE_SOURCE_FILES)
set(PUBLIC_INCLUDE_DIRS)
set(PRIVATE_INCLUDE_DIRS)

# TODO: make separate cmake function
foreach(ITEM IN LISTS MODULE_FILES)
    if (IS_DIRECTORY "${ITEM}")
        if (ITEM MATCHES "^(.*[\\\\/])?Public$")
            list(APPEND PUBLIC_INCLUDE_DIRS "${ITEM}")
        elseif (ITEM MATCHES "^(.*[\\\\/])?Private$")
            list(APPEND PRIVATE_INCLUDE_DIRS "${ITEM}")
        endif()
    else()
        list(APPEND MODULE_SOURCE_FILES ${ITEM})
    endif()
endforeach()

add_library(Engine STATIC)

# TODO: diff Public/Private source files
target_sources(Engine
    PUBLIC ${MODULE_SOURCE_FILES}
)

target_include_directories(Engine
    PUBLIC ${PUBLIC_INCLUDE_DIRS}
    PRIVATE ${PRIVATE_INCLUDE_DIRS}
)

add_library(Imber::Engine ALIAS Engine)
