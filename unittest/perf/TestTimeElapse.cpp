#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


class TimeElapse {
public:
    TimeElapse() {
        codeIn();
    }
    ~TimeElapse(){
        codeOut();
    }
    

    std::string toString() const {
        ostringstream oss;
        oss << "elapse: 100ms";
        return oss.str();
    }
private:
    int codeIn(){
        std::cout << "code in" << std::endl;
        return 0;
    }
    int codeOut(){
        std::cout << "code out" << std::endl;
        return 0;
    }

private:
};





TEST(TimeElapseTest, use){

    {
        TimeElapse te;

        int ilen = 100; 
        int jlen = 100;
        for(int i = 0; i < ilen; ++i){
            for(int j = 0; j < jlen; ++j){
                auto count =  1 + 3; 
                count += 4;
            }
        }
        std::cout << te.toString() << std::endl;

    }
}

