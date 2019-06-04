#include "gtest/gtest.h"
#include <iostream>

#include <functional>
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
    static int f1_1(int & a){
        std::cout << "args& :" << a << std::endl;
        return 0;
    }
    static int f1_2(const int & a){
        std::cout << "const args& :" << a << std::endl;
        return 0;
    }
    static void f1_ptr(int * p){
        std::cout << *p << std::endl;
    }
    static void f1_const_ptr(const int * p){
        std::cout << *p << std::endl;
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
        Caller<void> func(&FunctorTest::f0);
        func();
    }


    {
        Caller<int (int)> func(&FunctorTest::f1);
        func(1);
        int a = 1;
        func(a);

    }
    {
        Caller<int (int&)> func(&FunctorTest::f1_1);
        // func(1); // ERROR : const A1 &
        int a = 2;
        func(a);
    }
    {
        Caller<int (const int&)> func(&FunctorTest::f1_2);
        func(1);
    }
    {
        Caller<void (int *)> func(&FunctorTest::f1_ptr);
        int a = 3;
        int * p = &a;
        func(p);
    }
    {
        Caller<void (const int *)> func(&FunctorTest::f1_const_ptr);
        int a = 4;
        const int * cp = &a;
        func(cp);
    }



    {
        Caller<int (int,int)> func(&FunctorTest::f2);
        func(1,2);
    }
    {
        Caller<int (int, int, int)> func(&FunctorTest::f3);
        func(1, 2, 3);
    }
    {
        Caller<int (int, int, int, int)> func(&FunctorTest::f4);
        func(1, 2, 3, 4);
    }
}


TEST(StdFunctionTest, use){
    {
        std::function<void ()> func(&FunctorTest::f0);
        func();
    }


    {
        std::function<int (int)> func(&FunctorTest::f1);
        func(1);
        int a = 1;
        func(a);

    }
    {
        std::function<int (int&)> func(&FunctorTest::f1_1);
        // func(1); // ERROR : const A1 &
        int a = 2;
        func(a);
    }
    {
        std::function<int (const int&)> func(&FunctorTest::f1_2);
        func(1);
    }
    {
        std::function<void (int *)> func(&FunctorTest::f1_ptr);
        int a = 3;
        int * p = &a;
        func(p);
    }
    {
        std::function<void (const int *)> func(&FunctorTest::f1_const_ptr);
        int a = 4;
        const int * cp = &a;
        func(cp);
    }



    {
        std::function<int (int,int)> func(&FunctorTest::f2);
        func(1,2);
    }
    {
        std::function<int (int, int, int)> func(&FunctorTest::f3);
        func(1, 2, 3);
    }
    {
        std::function<int (int, int, int, int)> func(&FunctorTest::f4);
        func(1, 2, 3, 4);
    }
}
