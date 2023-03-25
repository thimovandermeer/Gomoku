add_subdirectory(validator_tests)
add_subdirectory(capture_tests)
target_sources(gomoku_test PRIVATE
		test.cpp
		)

