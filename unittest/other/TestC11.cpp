#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
TEST(C11Test, useFor){
    int arr [] = {1, 2, 3, 4, 5};
    for(auto &&  i : arr){
       cout << i << endl; 
    }

    for_each(begin(arr), end(arr), [](int i) {cout << i << endl;});
    for_each(begin(arr), end(arr), [](int i) {cout << i << endl;});
}

template<typename T, typename SrcType, typename IndexType = int>
class Reader {
public:
    /*
    class Iterator {
    public:
        Iterator(Reader * r, IndexType index):_r(r), _index(index){}
        ~Iterator(){}
         
        bool operator != (const Iterator & right){
            return _index < right._index;
        }
        const Iterator & operator ++(){
            ++_index;
            return *this;
        }
        T & operator *(){
            return (*_r)[_index];
        }
    private:
        Reader * _r;
        IndexType _index;
    };
    */
    typedef typename SrcType::iterator iterator;
    Reader(SrcType &src):_src(src){

    }
    ~Reader(){
    }

    iterator begin(){
        return _src.begin();
    }
    iterator end(){
        return _src.end();
    }

    T & operator [](IndexType index){
        return _src[index];
    }
private:
    SrcType & _src;
    friend class Iterator;
};

TEST(C11Test, useCustomFor){
    std::vector<double> arr;
    for(int i = 0; i < 10; i++){
        arr.push_back(10.03 + i);
    }
    Reader<double, std::vector<double>> r(arr);
    for( auto & v : r){
        v += 20;
        cout <<  "customer for " << v << endl;
    }
    {
        std::vector<int> arr;
        for(int i = 0; i < 10; i++){
            arr.push_back(1 + i);
        }
        Reader<int, std::vector<int>> r(arr);
        for(auto b = r.begin()
            , e = r.end(); 
            b != e; ++ b){
            *b += 10;
            cout << *b <<endl;
        }
    }
}


/*user: 
*     std::string str("1000");
*     f_0(str);
*/
void f_0(std::string & str){
    std::cout << str << std::endl;
}

/*user: 
*     f_1("100");
*     std::string str("1000");
*     f_1(str);
*/
void f_1(const std::string & str){
    //ERROR:  str = "1000";
    std::cout << str << std::endl;
}

TEST(C11Test, rightRef){
  
    std::string str("000");
    f_0(str);
    // f_0("100"); //complie ERROR

    f_1("100");
    f_1(str);

    std::cout << str  <<std::endl;
}

class A {
public:
    A(int i, int j)
    :_i(i), _j(j){
    }
    ~A(){}
    int get(){
        return _i + _j;
    }
private:
    int _i;
    int _j;
};

class B {
public:
    B(A * a)
    :_a(a), _k(0)
    {
    }
    B(A * a, int k)
    :_a(a), _k(k)
    {
    }
    int get(){
        return _a->get() + _k;
    }
private:
    A * _a;
    int _k;
};

TEST(C11Test, initializer){
    {
        std::vector<int> vec = {11111, 11112, 11113, 11114};
        for_each(begin(vec), end(vec), [](int i) {std::cout << i << std::endl;});
    }

    {
        A a {1, 2};
        ASSERT_TRUE( 3 == a.get());
    }

    {
        B b { new A{1, 3}};
        ASSERT_TRUE( 4 == b.get());
    }

    {
        B b { new A{1, 3}, 4};
        ASSERT_TRUE( 1+3+4 == b.get());
    }
    {
        std::vector<A*> vec = {new A{1,2}, new A{2, 2}, new A{3, 2}};
        for_each(begin(vec), end(vec), [](A* a) {std::cout << a->get() << std::endl;});
    }
    //TOOD: map
}


int f(int * a){
    return ++ (*a);
}
TEST(C11Test, functional){
    std::function<int (int *)> pf(f);
    int arg = 100;
    ASSERT_TRUE(101 == f(&arg));
}
