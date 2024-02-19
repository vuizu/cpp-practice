cmake_minimum_required(VERSION 3.21)
# 关闭非标准扩展功能，避免不同编译器之间的差异性，确保代码有良好的可移植性
set(CMAKE_CXX_EXTENSIONS OFF)

project("cpp-practice"
        VERSION 1.0
        DESCRIPTION "leaning c++/cuda"
        LANGUAGES CXX CUDA)

if (MVSC)
    add_compile_options("/source-charset:utf-8")
endif ()

# 指定标准库，MSVC指定不了，只有GCC和Clang可以 libc++ 和 libstdc++
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(CMAKE_CXX_STANDARD 17)

# 编译参数中是否手动指定C++版本 -std=c++, 确保CMake构建时不会受到外部环境中不必要的-std=c++设置的影响
string(FIND "${CMAKE_CXX_FLAGS}" "-std=c++" idx)
if (idx GREATER -1)
    message(WARNING "Please remove -std=c++ setting in ur env.")
endif ()

# find_package(OpenMP REQUIRED)

# CUDA on Windows 只能使用 Visual Studio 的 cl.exe 作为 C++ 的编译器
# C/C++ 和 Nsight Visual Studio Code Edition 插件需要将 cl.exe 放入 Path 中，否则会出现不明 bug
# find_package(CUDAToolkit REQUIRED)
# include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

add_subdirectory(src)