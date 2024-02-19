#include <iostream>
#include <string>
#include <type_traits>

int operator""_w(long double x) { return static_cast<int>(x * 2); }

struct S {
    char a;
    int b;
    long long c;
};

// 常量引用可以接受字面量
void fun(const int& par) {}

int main() {
    int x = 3.14_w;

    char* ptr = nullptr;
    void* v_ptr = ptr;

    if (!ptr && x) {
        std::cout << "char out" << std::endl;
    }

    // 指针的引用
    int y = 10;
    int* y_ptr = &y;
    int*& ref = y_ptr;
    std::cout << *ref << std::endl;

    int z = 30;
    fun(40);

    int k{};
    // c++17 以上才有is_same_v
    // decltype(obj) -> 通常来说，表达式会包含操作符
    /*
        std::cout << std::is_same_v<decltype(k), int> << std::endl;

        // decltype(表达式) -> lvalue、glvalue
        std::cout << std::is_same_v<decltype((k)), int&> << std::endl;
        // decltype(表达式) -> rvalue、prvalue
        std::cout << std::is_same_v<decltype(k + 1), int> << std::endl;
        std::cout << std::is_same_v<decltype((k + 1)), int> << std::endl;
        // decltype(字面量) -> 字面量为最基本的表达式，且为右值
        // 变量也为最基本的表达式，但是通常需要包含操作符。
        std::cout << std::is_same_v<decltype(1), int> << std::endl;
        // decltype(表达式) -> xvalue
        std::cout << std::is_same_v<decltype(std::move(k)), int&&> << std::endl;
    */
}