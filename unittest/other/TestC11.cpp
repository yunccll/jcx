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
