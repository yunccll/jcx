#include "gtest/gtest.h"

#include <jcx/base/Iterator.h>

#include <vector>
#include <unordered_map>


TEST(IteratorTest, vectorUse){
    std::vector<int> vec {1, 2 ,3, 4, 5, 6};
    jcx::base::Iterator<std::vector<int>> it(vec);
    
    while(it.hasNext()){
        auto & v = it.next();
        std::cout << v << std::endl;
    }
}

TEST(IteratorTest, hashMapUse){
    std::unordered_map<std::string, int *> hash {
        std::make_pair<std::string, int*>("api", new int(1)),
        std::make_pair<std::string, int*>("p1", new int(2)),
        std::make_pair<std::string, int*>("p2", new int(3)),
    };

    jcx::base::Iterator<std::unordered_map<std::string, int*>> it(hash);

    while(it.hasNext()){
        auto & v = it.next();
        std::cout << v.first << " " << *(v.second) << std::endl;
    }
}


TEST(IteratorTest, customerContainer){
}

