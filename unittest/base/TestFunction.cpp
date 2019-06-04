#include "gtest/gtest.h"
#include <functional>


template<typename T>
class FunctionTable {
public:
    FunctionTable(){}
    virtual ~FunctionTable(){}

    void put(char ch, std::function<int (int)> cb){
        functions[(int)ch] = cb;
    }
    std::function<int (int)>  get(char ch){
        return functions[(int)ch];
    }
private:
    std::function<int (int)> functions[256];
};


class A {
public:
    int add(int v){
        return v+1;
    }
    int add2(int v){
        return v + 2;
    }
};

class GtpFunctionTable : public FunctionTable<A>{
public:
    GtpFunctionTable(A & a){
        put('1', std::bind(&A::add, &a, std::placeholders::_1));
        put('2', std::bind(&A::add2, &a, std::placeholders::_1));
    }
    ~GtpFunctionTable(){
    }
};

TEST(FunctionTest, use){
    std::cout << "...........functional" << std::endl;

    A a;
    GtpFunctionTable ft(a);
    ASSERT_TRUE(11 == ft.get('1')(10));
    ASSERT_TRUE(12 == ft.get('2')(10));

    ASSERT_TRUE(true);
    //ASSERT_FALSE
}

