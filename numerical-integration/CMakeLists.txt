cmake_minimum_required(VERSION 3.10)

project(numerical_integration)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

SET_SOURCE_FILES_PROPERTIES(scalar.cpp PROPERTIES COMPILE_FLAGS "-march=native -O3 -ffast-math")
SET_SOURCE_FILES_PROPERTIES(scalar_no_avx.cpp PROPERTIES COMPILE_FLAGS "-mno-sse2 -mno-avx -mno-avx2 -mno-avx512f -march=native -O3 -ffast-math")
SET_SOURCE_FILES_PROPERTIES(scalar_avx512.cpp PROPERTIES COMPILE_FLAGS "-mprefer-vector-width=256 -march=native -O3 -ffast-math")
SET_SOURCE_FILES_PROPERTIES(vectorized.cpp PROPERTIES COMPILE_FLAGS "-march=native -O3 -ffast-math")

add_executable(main test_main.cpp scalar.cpp scalar_no_avx.cpp scalar_avx512.cpp vectorized.cpp)
target_link_libraries(main PRIVATE Threads::Threads benchmark)

