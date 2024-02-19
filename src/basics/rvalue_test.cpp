#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

/// https://zh.cppreference.com/w/cpp/language/value_category
class A {
public:
    A(size_t size) : size(size), array((int*) malloc(sizeof(int) * size)) {
        std::cout << "constructor called." << std::endl;
    }

    ~A() {
        // delete[] array;
        free(array);
    }

    A(const A& a) : size(a.size) {
        array = new int[a.size];
        std::cout << "normal copied, memory at: " << array << std::endl;
    }

    A(A&& a) : array(a.array), size(a.size) {
        a.array = nullptr;
        std::cout << "xvalue copied, memory at: " << array << std::endl;
    }

    const int* get_array() const {
        return array;
    }

private:
    size_t size;
    int*   array;
};

int main() {
    auto get_temp_a = [](size_t size = 100) -> A {
        auto tmp = A(size);
        std::cout << "Memory at: " << tmp.get_array() << std::endl;
        return tmp;
    };

    std::cout << std::is_rvalue_reference<decltype(get_temp_a())&&>::value << std::endl;
    std::cout << std::is_same<decltype(get_temp_a()), A>::value << std::endl;


    // A&&  x = get_temp_a(1000);
    // auto y = x;

    // 字符串为左值

    // 右值引用就是对右值的引用，= 右边必须为右值
    // 这里的 z 定义为右值引用
    A&&         z = A(100);
    // A&& t = std::move(z);，其中 decltype(z) 中的 z 表示为将亡值，而后面使用的 z 表示为左值，需要将其转为右值
    // 即使变量的类型是右值引用，由它的名字构成的表达式仍是左值表达式
    decltype(z) t = std::move(z);


    //以下例子可说明decltype中的表达式只会获取值，并不会执行计算
    // 其中 ++k 为左值，k++ 为纯右值
    int           k = 0;
    decltype(++k) i = k;
    decltype(k++) j;
    std::cout << k << std::endl;


    // 下标表达式 []，为左值，跟里面存储元素类型无关
    int              arr[] = { 1 };
    decltype(arr[0]) l     = k;
}