cmake_minimum_required(VERSION 2.8)

project(nandtools C)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
add_definitions("-Wall -Wextra -pedantic")

execute_process(
	COMMAND git rev-parse --abbrev-ref HEAD
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_BRANCH
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
	COMMAND git log -1 --format=%h
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_COMMIT_HASH
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
configure_file(
	${CMAKE_SOURCE_DIR}/version.h.in
	${CMAKE_SOURCE_DIR}/version.h
)

add_executable(
	nand_clean_oob
	nand.c
	nand_clean_oob.c
)

install(TARGETS nand_clean_oob DESTINATION bin/)
