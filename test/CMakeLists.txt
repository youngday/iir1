cmake_minimum_required(VERSION 3.5)
enable_testing()

add_executable (test_butterworth butterworth.cpp)
target_link_libraries(test_butterworth iir)
add_test(TestButterworth test_butterworth)

add_executable (test_chebyshev1 chebyshev1.cpp)
target_link_libraries(test_chebyshev1 iir)
add_test(TestChebyshev1 test_chebyshev1)

add_executable (test_chebyshev2 chebyshev2.cpp)
target_link_libraries(test_chebyshev2 iir)
add_test(TestChebyshev2 test_chebyshev2)