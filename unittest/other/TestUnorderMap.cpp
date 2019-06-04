#include "gtest/gtest.h"
#include <iostream>

#include <unordered_map>
#include <string>


TEST(HashMapTest, iterator){
    std::unordered_map<std::string, int *> hash {
        std::make_pair<std::string, int*>("api", new int(1)),
        std::make_pair<std::string, int*>("p1", new int(2)),
        std::make_pair<std::string, int*>("p2", new int(3)),
        };

    ASSERT_TRUE( *(hash["api"]) == 1);

    auto it = hash.begin();
    for(; it != hash.end(); ++it){
       std::cout << it->first <<  " " << it->second << std::endl;
       ASSERT_TRUE (*(it->second) < 4);
    }
}
