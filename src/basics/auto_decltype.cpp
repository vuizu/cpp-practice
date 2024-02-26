#include <bitset>
#include <cstdlib>
#include <iostream>
#include <string>

/// https://zh.cppreference.com/w/cpp/language/decltype
/// decltype 的参数需要在编译期就能确定类型

// 这里提供了给 C 语言调用的接口，因为 C 中没有函数重载
// 其签名为 test
extern "C" void test() {
}

// 如果加上会编译报错，其签名为 _testii
// extern "C"
void test(int x) {
}

class A {
public:
    int q;
};

void mystery(char* s1, const char* s2) {
    while (*s1 != '\0')
        s1++;

    for (; *s1 != *s2; s1++, s2++) {
        printf("%d, %d\n", *s1, *s2);
    }
}

int main() {

    int               k = 1;
    decltype((A().q)) p = std::move(k);


    int  arr[] { 1, 2, 3 };
    int* ptr = arr;


    int* ip = (int*) malloc(3 * sizeof(int));
    free(ip);


    // 移位运算符是对补码进行操作的

    std::cout << std::bitset<sizeof(int) * 8>(-1) << std::endl;
    // std::cout << binary << std::endl;

    int nxt = -2 << 1;
    std::cout << std::bitset<sizeof(int) * 8>(nxt) << "\t" << nxt << std::endl;

    int kk = 1 ^ 2;
}
