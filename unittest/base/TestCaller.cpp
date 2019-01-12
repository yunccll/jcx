#include "gtest/gtest.h"
#include <iostream>

#include <jcx/base/Caller.h>



using namespace jcx;
using namespace base;

struct FunctorTest{
    static void f0(){
        std::cout << "args:0" << std::endl;
    }
    static int f1(int a){
        std::cout << "args:" << a << std::endl;
        return 0;
    }
    static int f2(int a, int b){
        std::cout << "args:2 -> a:" << a << ", b:" << b << std::endl;
        return 0;
    }
    static int f3(int a, int b, int c){
        std::cout << "args:3 " << std::endl;
        return 0;
    }
    static int f4(int a, int b, int c, int d){
        std::cout << "args:4 " << std::endl;
        return 0;
    }
};
TEST(CallerTest, use){
    {
        Caller0<void> func(&FunctorTest::f0);
        func();
    }
    {
        Caller1<int, int> func(&FunctorTest::f1);
        func(1);
    }
    {
        Caller2<int, int, int> func(&FunctorTest::f2);
        func(1,2);
    }
    {
        Caller3<int, int, int, int> func(&FunctorTest::f3);
        func(1, 2, 3);
    }
    {
        Caller4<int, int, int, int, int> func(&FunctorTest::f4);
        func(1, 2, 3, 4);
    }
}
