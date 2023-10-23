#if 0  // readme , linux
download from : https://github.com/fmtlib/fmt/releases/download/10.1.0/fmt-10.1.0.zip
mkdir bld && cd bld && cmake .. && make 
now we see libfmt.a 
g++ -I../include   main.cpp   libfmt.a && ./a.out
#endif 

#if 0 // windows 
del *.obj

set SRC=D:\jd\t\git\fmt-master\src
set INC=D:\jd\t\git\fmt-master\include
set FALSE=(1 equ 0)

if %FALSE% (
cl  /O2 /c %SRC%\format.cc  /I%INC%
cl  /O2 /c %SRC%\os.cc  /I%INC%
lib format.obj os.obj /out:fmt.lib
)

cl  /O2 /std:c++20 /EHsc /c .\main.cpp  /I%INC%
cl /O2 /EHsc main.obj fmt.lib /I%INC% /Fe"mainapp.exe" && .\mainapp.exe

#endif 



#include <iostream>
#include <vector>
#include <fmt/ranges.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/xchar.h>
#include <fmt/os.h>
#include "fmt/std.h"

#include <map>
#include <unordered_map>
#include <bitset>


#include <cassert>



using namespace std; 


int main()
{
    cout << 1111 << endl;

    vector<int> vi{1,2,3,4,5,6,7,8};

    fmt::print("{}\n", vi);
    fmt::print("{0},{2},{1}\n", "hello", string("world"), 1024); 
    string s = fmt::format("{0},{2:08d},{1}\n", "hello", string("world"), 1024); 
    cout << s << endl;

    string myname="JD"; 
    using namespace fmt::literals;
    fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.\n", "name"_a=myname, "number"_a=42);

    char buf[1024] = {0}; 
    auto tt = fmt::format_to(buf,  "{} {}\n", "hello world", 1024); 
    cout << string(buf) << endl; 

    fmt::text_style ts = fg(fmt::rgb(0, 200, 30));
    std::string out;
    fmt::format_to(std::back_inserter(out), ts, FMT_STRING("rgb(255,20,30){}{}{}"), 1, 2, 3);  // works on git bash

    //cout << out << endl; 


    std::vector<char> hello = {'h', 'e', 'l', 'l', 'o'};
    s = fmt::format(FMT_STRING("{}"), hello); // 'h',...

    s = fmt::to_string(1.24f);

    s = fmt::format("{0:<10}___", "012");  // left align
    s = fmt::format("{0:^10}___", "012");  // center align
    s = fmt::format("{0:+}___", 12);  // show + or - , always 
    s = fmt::format("{0: }___", -12);  // show " " or - , always 
    s = fmt::format("{0:#b}___", -12);  // binary string "0b0101xxx", b,x,o,e
    s = fmt::format("{0:b}", 13);  // 
    s = fmt::format("{}", true); 
    s = fmt::format("{{neverchange}}"); 

    uint64_t addr = 0x123456; 
    s = fmt::format("{}", fmt::ptr((uint64_t*)addr));  //   addr to 0x 


    auto end = fmt::format_to(buf, "{}","012");
    assert(end - buf == 3); 


    std::string sb;
    fmt::format_to(std::back_inserter(sb), "part{}+", 1);
    fmt::format_to(std::back_inserter(sb), "part{}", 2);
    cout << sb << endl; 

    s = fmt::to_string(fmt::join(vi.begin()+2, vi.begin()+6, "+"));
    s = fmt::format("{}", fmt::join(vi.begin(),vi.begin()+7,"+")); 

    fmt::ostream of_ = fmt::output_file("test-file");
    vector<string> vcontent = {"hello", "world","me"};
    for(auto e: vcontent)
    {
        of_.print("{}",e); 
    }
    of_.flush();


    s=fmt::format("{}",(fmt::join(vi, "+")));

    int arr[2][3]={ {1,2,3},{4,5,6}};
    s = fmt::format("{}", arr); 

    vector<vector<string>> vstr={ {"ab","cd","ef"},{"gh","gj"} };
    s = fmt::format("{:n:n}",vstr);  // "ab",..."gj"


    std::map<string, int> m_s_i{{"k1",1}, {"k2",2}};
    s = fmt::format("{}",m_s_i);

    std::unordered_map<string,int> um_s_i{{"k1_",1}, {"k2_",2}};
    s = fmt::format("{}",um_s_i);
    auto tp = std::tuple<int, float, std::string, char>(42, 1.5f, "this is tuple", 'i');
    s = fmt::format("{}", tp);

    auto bval = bitset<32>("0111111111111"); 
    bitset<32> bv("0111111111111");
    s = fmt::format("{}--{}", bv, bv[1]);

    cout << s << endl; 
    return 0; 
}
