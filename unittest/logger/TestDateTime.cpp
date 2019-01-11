#include "gtest/gtest.h"
#include <jcx/logger/DateTime.h>


using namespace jcx;
using namespace logger;
TEST(DateTimeTest, initTabs){
    auto ptr = DateTime::now();
    {
        char buf[21] = {0};
        ASSERT_EQ(19, ptr->fill(buf, sizeof(buf)));
    }

    {
        char buf[10] = {0};
        ASSERT_EQ(-1, ptr->fill(buf, sizeof(buf)));
    }
}

TEST(DateTimeTest, statiUse){
    static DateTime now;

    char buf[21] = {0};
    ASSERT_EQ(19, now.fill(buf, sizeof(buf)));
    printf("now:%s\n", buf);

    now.refresh();
    ASSERT_EQ(19, now.fill(buf, sizeof(buf)));
    printf("now:%s\n", buf);

    now.refresh();
    ASSERT_EQ(19, now.fill(buf, sizeof(buf)));
    printf("now:%s\n", buf);

}

