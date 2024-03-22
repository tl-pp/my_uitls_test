#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <chrono>


#include "fmt_test.hpp"

CFmtTest::CFmtTest() 
{  
    std::cout << fmt::format("{:=^60}", "create CFmtTest") << std::endl;
}

CFmtTest::~CFmtTest() 
{
    std::cout << fmt::format("{:=^60}", "destroy CFmtTest") << std::endl;
}

int CFmtTest::FmtTest( )
{
    // 1.Result Print "Hello, world!"
    fmt::print("Hello, world!\n");

    // 2.Result: "a, b, c"
    std::string s = fmt::format("string {}, {}, {}", 'a', 'b', 'c');
    std::cout <<  s << std::endl;
    std::cout << fmt::format("a->c {0}, {1}, {2}", 'a', 'b', 'c') << std::endl;
    std::cout << fmt::format("c->a {2}, {1}, {0}", 'a', 'b', 'c') << std::endl;
    std::cout << fmt::format("ascii : {:d}, {:d}, {:d}", 'a', 'b', 'c') << std::endl;
    
    // 3.Result: "Elapsed time: 1.23 seconds"
    std::cout << fmt::format("Elapsed time: {s:.2f} seconds", fmt::arg("s", 1.23)) << std::endl;

    /*4. 段落格式:
        '<'     左对齐
        '>'     右对齐
        '^'     居中
    */ 

    std::cout << fmt::format("{:<30}", "left aligned") << std::endl;
    std::cout << fmt::format("{:>30}", "right aligned") << std::endl;
    std::cout << fmt::format("{:^30}", "centered") << std::endl;
    std::cout << fmt::format("{:*^30}", "centered") << std::endl;

    /*5. 输出格式
        's'     字符串
        'c'     字符
        'p'     指针
        整数---------------
        'b'     二进制
        'B'     二进制
        'd'     十进制
        'o'     八进制
        'x'     十六进制
        'X'     十六进制
        none    和'd'一样
        浮点数-------------
        'a'     十六进制输出，有前缀0x,小写字符。使用’p’来表示指数
        'A'     和’a’一样，只是输出为大写字符。
        'e'     科学计数法，使用‘e’来表示指数部分。
        'E'     和'e'一样，但是分隔符为大写'E'
        'f'     定点输出。
        'F'     和'f'一样, 但是会把nan替换为NAN,inf替换为INF。
        'g'     如果精度p>=1, 会圆整到该精度。会根据简洁性选择定点或浮点输出。
        'G'     和'g'一样，但是会大写。
        none    和'g'一样, 但是默认精度为能表达值的最大精度
    */

    char test_a = 'a';

    std::cout << fmt::format("char: {0:c}; addr: {1:p}", test_a, &test_a) << std::endl;
    std::cout << fmt::format("int: {0:d}, {0};  hex: {0:x}, {0:X};  oct: {0:o}; bin: {0:b}, {0:B}", 33) << std::endl;
    std::cout << fmt::format("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 33) << std::endl;

    std::cout << fmt::format("float: {:.{}f}", 3.14, 1) << std::endl;

    // 6. 支持tuple pair vector
    std::tuple<char, int, float> t{'a', 1, 2.0f};
    std::cout << fmt::format("tuple: {}", t) << std::endl;
    std::pair<char, int> p{'a', 1};
    std::cout << fmt::format("pair: {}", p) << std::endl;

    // std::vector<int> vec = {10, 20, 30};
    std::vector<int> vec = {10,20,30};
    std::cout << fmt::format("vec:{}", vec)<< std::endl;
    std::cout << fmt::format("vec hex:{::x}", vec) << std::endl;
    std::cout << fmt::format("vec hex:{::#x}", vec) << std::endl;
    std::cout << fmt::format("vec: {}", fmt::join(vec, ", ")) << std::endl;
    
    // 7 时间
    auto now = std::chrono::system_clock::now();
    std::cout << fmt::format("date and time :{}", now) << std::endl;
    std::cout << fmt::format("Time: {:%H:%M}\n", now) << std::endl;

    // 8 自定义类型
    point x = {1,2};
    std::cout << fmt::format("point:{}", x) << std::endl;

    // 9 对 osstream的支持
    std::cout << fmt::format("The date is {}", date{2012, 12, 9}) << std::endl;

    // 10.矩形
    fmt::print(
    "┌{0:─^{2}}┐\n"
    "│{1: ^{2}}│\n"
    "└{0:─^{2}}┘\n", "", "Hello, world!", 20);

    // 11.编译期格式化 使用宏FMT_COMPILE包含格式化字符串，如果编译期支持 C++17的constexpr if，那么将会进行编译期的格式化。
    std::string s_compilt = fmt::format(FMT_COMPILE("{}"), 42);

    // 12. 文件
    fmt::print(stderr, "Don't {}!\n", "panic");

    auto out = fmt::output_file("guide.txt");
    out.print("Don't {}\n", "Panic");

    return 0;
}
