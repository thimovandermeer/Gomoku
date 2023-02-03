cmake_minimum_required(VERSION 3.23)
project(gomoku)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(EXTRA_COMPILER_FLAGS
		"-Wall
		-Wextra
		-Werror
		-g3
		-fsanitize=address"
		)

add_executable(gomoku main.cpp)
add_subdirectory(src)
target_include_directories(gomoku PUBLIC inc)
target_compile_options(gomoku PUBLIC
		${EXTRA_COMPILER_FLAGS}
		)
target_link_options(gomoku PUBLIC
		-fsanitize=address
		)

add_executable(gomoku_test
#		test sources in `test` folder
		)
add_subdirectory(test)
target_link_libraries( gomoku_test
		GTest::gtest_main
)
