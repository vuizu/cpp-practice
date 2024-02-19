find_package(OpenMP REQUIRED)
if (OpenMP_FOUND)
    message(STATUS "openmp found. OpenMP_CXX_FLAGS: " ${OpenMP_CXX_FLAGS})
endif ()

# 仅针对本 target 的编译选项
add_compile_options("-fopenmp")

add_executable(omp_test omp_test.cpp)
target_link_libraries(omp_test OpenMP::OpenMP_CXX)