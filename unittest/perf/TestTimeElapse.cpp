#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <unistd.h>
#include <unordered_map>
#include <parallel_hashmap/phmap.h>
using phmap::flat_hash_map;
using phmap::parallel_flat_hash_map;


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
TEST(TimeElapseTest, flat_hash_map){
    typedef flat_hash_map<std::string, int> HashMap;
    //typedef parallel_flat_hash_map<std::string, int> HashMap;
    HashMap map;

    struct  timeval start;
    gettimeofday(&start,NULL);

    int max = 2000*1000;
    for(int i = 0; i < max; ++i){
        map[to_string(i)] = i;
        //map.insert(HashMap::value_type(buf, i));
    }

    struct  timeval end;
    gettimeofday(&end,NULL);
    unsigned  long diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("diff: %fms, tps:%fM\n",diff/1000.0, 1.0*max/diff);
}

TEST(TimeElapseTest, stl_hash_map){
    typedef std::unordered_map<std::string, int> hashmap;
    hashmap map;

    struct  timeval start;
    gettimeofday(&start,NULL);

    int max = 2000*1000;
    for(int i = 0; i < max; ++i){
        //map.insert(hashmap::value_type(buf, i));
        map[to_string(i)]=i;
        //map.find(std::string("hello") + std::to_string(i));
    }

    struct  timeval end;
    gettimeofday(&end,NULL);
    unsigned  long diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("diff: %fms, tps:%fM\n",diff/1000.0, 1.0*max/diff);
}

