file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)
add_definitions(-DLISP_DEBUG)
add_executable(lisp ${SOURCES})
target_include_directories(lisp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})