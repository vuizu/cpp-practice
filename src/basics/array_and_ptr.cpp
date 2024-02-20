// #include <format>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

void test(char* ar) {
}

/*
 - 不能使用 auto 来声明数组类型 ->
 - 数组不能复制
 - 元素个数必须是一个常量表达式，C 中支持变长数组，所以 C++ 也支持，但是 C++ 标准中不支持，需要加上 -pedantic-errors
 - 字符串数组的特殊性

 定义一个数组必须 指定数组长度 或者 进行初始化，不要使用 extern 指针来声明数组
 数组定义好后是不可以 assignment 的

 方法中的接收的 形参数组 都会转为 指针: `void func(int arr[2])` -> `void func(int* arr)`

 数组 int arr[1] 的类型为 int[1]，和 int a 的类型不一样，不是 int.

 指针数组：int  *a [3];  -> decltype(a) == int * [3]
                        -> int *a[3] = { &x1, &x2, &x3 }; -> int x1, x2, x3;
 引用数组：int  &a [3];  -> 错误语法


 数组指针：int (*a)[3];  -> decltype(a) == int(*)[3]
                        -> int (*a)[3] = &b; -> int b[3];
 数组引用：int (&a)[3];
*/
int main() {
    int a[] { 2, 3, 4, 5 };
    // 数组使用时通常会转换成相应的指针类型
    // 使用数组对象时，通常情况下会产生数组到指针的隐式转换
    // 隐式转换会丢失一部分类型信息
    // 可以通过声明引用来避免隐式转换
    // a 会被视为指针，指针操作如下：
    // a[x] -> *(a + x) -> x[a]也是可以的
    // 指针是可以往前后一直走的，此时 x 需要手动保证不越界，否则 a[-1]、a[10] 都能通过编译，但是会产生未定义行为

    // 数组名会自动转换为指向其第一个元素的指针的几种情况：
    // 一. 将数组名作为实参传递给函数时
    //     -> void t(int arr[]);
    //     -> 当传入 int a[3] = { 1, 2, 3 }; 时
    //     -> 函数实际的签名为：void t(int* arr); 故 实参a 会被转变成指针
    //     -> 即使你的函数签名为 void t(int arr[100000]);，也会被指针替换
    //     -> 二维数组 void t(int arr[][3]);, 会将第一个[]进行指针化 => void t(int(* arr)[3]);
    //     -> 二维数组的本质就是 指向一维数组的指针，也就是数组的指针
    // 二. 当使用数组名进行赋值或初始化操作时

    int* p = (int*) (&a + 1);

    int b = *(a + 1);    // 3
    int c = *(p - 2);    // 5

    std::cout
        << b
        << "\t"
        << c
        << std::endl;


    std::cout
        << p << "\t"
        << &a << "\t"
        << &a + 1 << "\t"
        << std::endl;


    int* ptr         = a;
    int(&arr_ref)[4] = a;
    int(*arr_ptr)[4] = &a;

    const int     i = 1 + 2;
    constexpr int j = 1 + 2;


    int  z[] = { 1, 2, 3 };
    auto w   = z;

    w[0] = 2;
    std::cout << z[0] << std::endl;


    const char h_str[] = "hello";
    std::cout << std::is_same<decltype(h_str), const char[6]>::value << std::endl;


    // ============================================
    std::string  s     = "123";
    std::string* s_ptr = &s;


    const char* s_v     = "123";
    auto        s_v_ptr = &s_v;


    const char s_vv[]   = "123";
    auto       s_vv_ptr = &s_vv;


    const char s_vvv[]   = { '1', '2', '3', '\0' };
    auto       s_vvv_ptr = &s_vvv;


    const char(*str)[4] = &"123";
    // ============================================


    std::cout << sizeof(s_vvv) << std::endl;


    int  tmp[2]  = { 1, 2 };
    int* tmp_ptr = tmp;


    std::cout << &tmp << "\t"
              << tmp_ptr << "\t"
              << tmp << "\t"
              << *tmp_ptr << "\t"
              << &(tmp[0]) << "\t"
              << &tmp_ptr << "\t"
              << *(&tmp_ptr) << "\n"
              << tmp << "\t" << std::begin(tmp) << "\t" << &tmp[0] << "\n"
              << tmp + 2 << "\t" << std::end(tmp) << "\t" << &tmp[2] << "\t" << tmp_ptr[0]
              << std::endl;

    int xx = 0 [tmp];
    std::cout << xx << std::endl;

    auto t = std::cbegin(tmp);
    // std::begin  => int*
    // std::cbegin => const int*，不是int* const，前者是 数组 中的每个元素都不能修改，后者是 数组 不能修改（数组特性）

    // 指针相减，得到的结果会自动除以 sizeof(...)，如果需要得到两指针相差的字节数需要手动乘以 sizeof(...)
    int* tmp_ptr2 = tmp + 2;
    std::cout << (tmp_ptr2 - tmp_ptr) << "\t" << (tmp_ptr2 - tmp_ptr) * sizeof(int) << std::endl;

    // 使用std::array或者std::vector，避免数组名隐式转换为指向数组第一个元素的指针
    std::vector<int> v { 1, 2, 3 };
    // 其中 v 是一个对象，&v 是该对象的地址，需要使用别的方法访问内部的数据
    // 可以使用下标来访问 []，对象内部保存了起始地址，本质上都是在起始地址上操作
    // 所以 begin 和 end 方法原理都是：操作对象内部的数据的 起始地址 和 终止地址
    std::cout << &v[0] << "\t" << &(*std::cbegin(v)) << "\t" << &(*v.begin()) << std::endl;


    auto svv = s_vv;
    while (*svv) {
        std::cout << *svv << std::endl;
        svv++;
    }

    // 多维数组 -> 本质为数组的数组

    int x[][2] { { 1 }, { 2 } };    // 只能省略第一个大小，int x[][] 不能通过编译
    int x1[2][3] {
        {1, 2, 3}
    };
    for (int i = 0; i < 2; i++) {
        std::cout << x1[i] << "\t" << &x1[i][0] << std::endl;
    }

    auto& x1_type = x1[0];
    auto& x_type  = x1;
    auto  x_ptr   = x;

    int* x_t[3];

    std::cout << x1[1] - x1[0] << std::endl;

    for (int i : x1[1]) {
        std::cout << i << std::endl;
    }

    std::cout << std::endl;

    // c++11 ISO 标准不允许将 字符串字面量转成 char*，只能转为 const char*
    // 或者使用数组进行接收
    const char ar[] { 'a', 'b', 'c', '\0' };
    test(const_cast<char*>(ar));


    std::string a1 = "hello ";
    std::string a2 = "world";

    a2 = a1 + a2;


    // 直接打印指针是打印指针所保存的地址的值，而不是指针自身的地址，效果等同于基本数据类型的打印，而不同于对象引用类型的打印。
    int  nums[] { 1, 2, 3 };
    auto num_ptr  = &nums[0];
    auto nums_ptr = &nums;
    // 函数名是指向方法的指针
    auto vari     = main;

    // 一般的计算机以字节编址 + 小端序（低地址存放数据的低位，比如一个 int 类型的值 1 -> 01 00 00 00，由于是按字节编址，刚好 4 个字节）


    // 汇编，而栈是向低地址生长的
    // ax 是16位的 x86CPU 的寄存器，eax 是32位的 x86CPU 的寄存器，而 rax 是64位的 x86CPU 的寄存器，ax只是 eax 的低16位，eax 只是 rax 的低32位。
    // BYTE 表示占用 1 个字节，WORD 表示占用 2 个字节，DWORD 表示占用 4 个字节，QWORD 表示占用 8 个字节
}