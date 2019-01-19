#include "gtest/gtest.h"
#include <iostream>
#include <vector>

void haha(int & a){
    std::cout << a << std::endl;
}
void haha_const_ref(const int & a){
    std::cout << a << std::endl;
}
TEST(CppTest, ref){
    //haha(1); //ERROR
    int a = 1;
    haha(a); //OK

    haha_const_ref(1);
    haha_const_ref(a);
    const int const_a = 100;
    haha_const_ref(const_a);
}



// const int * ------cannot push_back to ----> vector<int*>
TEST(CppTest, const_int_ptr){
    std::vector<int*> vec;
    int a = 100;
    // const int * ca = &a; // cannot push_back to vector<int*>
    int * ca = &a;
    vec.push_back(ca);
}
