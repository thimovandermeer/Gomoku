cmake_minimum_required(VERSION 3.22)
project(gomoku)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG v1.13.0
)

FetchContent_Declare(
		SFML
		GIT_REPOSITORY https://github.com/SFML/SFML.git
		GIT_TAG 8a307df494d1a8934384d8861cad3a1b9dbaaaba # 2.6
)

FetchContent_Declare(
		fmtlib
		GIT_REPOSITORY https://github.com/fmtlib/fmt.git
		GIT_TAG 9.1.0
)

FetchContent_MakeAvailable(googletest SFML fmtlib)

enable_testing()

set(EXTRA_COMPILER_FLAGS
		-Wall
		-Wextra
#		-Werror
		-g3
		-fsanitize=address
		)

add_executable(gomoku main.cpp)
target_include_directories(gomoku PUBLIC inc)
target_include_directories (gomoku PUBLIC usr/local/opt/freetype/include/freetype2)
target_compile_options(gomoku PUBLIC
		${EXTRA_COMPILER_FLAGS}
		)
target_link_options(gomoku PUBLIC
		-fsanitize=address
		)
target_link_libraries(gomoku
		sfml-graphics
		fmt::fmt
		)

target_compile_definitions(gomoku PUBLIC PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

add_executable(gomoku_test
#		test sources in `test` folder
		)
target_include_directories(gomoku_test PUBLIC inc)
target_link_libraries(gomoku_test
		GTest::gtest_main
		sfml-graphics
		fmt::fmt
		)

add_subdirectory(src)
add_subdirectory(test)