#include <algorithm>
#include <bits/stdc++.h>
#include <initializer_list>
#include <iostream>
#include <omp.h>
#include <vector>

struct S {
    int         a;
    int         b;
    const char* str;
};

class Foo { };

int main(int argc, char* argv[]) {

    int  x = 2;
    int* arr[x];


    int(*a)[x];

    auto b = { 1, 2, 3 };

    std::vector<int> v { 1, 2, 3 };    // 123
    std::vector<int> v2 = {};          // 345

    std::for_each(v.begin(), v.end(),
                  [](int val) { std::cout << val << std::endl; });

    for (int i : { 1, 2, 3 }) {
    }

    std::cout << sizeof(arr) << std::endl;

    const char* str = "hello";
    switch (x) {
    case 2:
        std::cout << x;
    }

    void* const* t = nullptr;


    // todo 1. [[fallthrough]]
    int k;
    switch (k) {
    case 1:
        std::cout << 1 << std::endl;
        [[fallthrough]];
    case 2:
        std::cout << 2 << std::endl;
        break;
    default:
        std::cout << "nonthing" << std::endl;
    }


    // todo 2. for range-based, 最终将被编译器翻译成容器 begin 和 end 的 for 循环
    // 这里的 _ 是变量名，而不是特殊名字
    for (int _ : { 1, 2, 3 }) {
        std::cout << " " << std::endl;
    }


    // std::format, gcc 版本为13.1，clang 版本为17.0.1 才支持
    // std::format("My name is {}", "zhangsan");
}
