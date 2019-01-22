#include "gtest/gtest.h"
#include <jcx/base/SimpleContainer.h>

using namespace jcx;
using namespace base;

TEST(__Container, use){
    {
        __Container<std::vector<int>> c;
        c.insert(1);
        c.insert(2);
        c.insert(1);
        c.insert(1);
        ASSERT_TRUE(c.size() == 4);
        c.remove(1);
        ASSERT_TRUE(c.size() == 3);
        c.removeAll(1);
        ASSERT_TRUE(c.size() == 1);
    }
    {
        __Container<std::list<int>> c;
        c.insert(1);
        c.insert(1);
        c.insert(1);
        c.insert(1);
        ASSERT_TRUE(c.size() == 4);
    }
}
TEST(SimpleVectorTest, use){
    {
        SimpleVector<int> c;
        c.insert(1);
        c.insert(1);
        c.insert(1);
        c.insert(1);
        ASSERT_TRUE(c.size() == 4);
    }
}

TEST(SimpleListTest, use){
    {
        SimpleList<int> c;
        c.insert(1);
        c.insert(1);
        c.insert(1);
        c.insert(1);
        ASSERT_TRUE(c.size() == 4);
    }
}
