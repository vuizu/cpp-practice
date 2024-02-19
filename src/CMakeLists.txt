# add_library(cu main.cu)
# include只是头文件，真正运行的还是库文件
#target_include_directories(cu PRIVATE ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

# target_link_libraries 对每个target只能使用一次
# target_link_libraries(main cu OpenMP::OpenMP_CXX CUDA::cudart)
# target_link_libraries(main cu)

add_subdirectory(basics)
add_subdirectory(omp)
add_subdirectory(cuda)
add_subdirectory(opencl)