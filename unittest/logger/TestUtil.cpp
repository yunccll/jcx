#include "gtest/gtest.h"

#include <jcx/logger/DateTime.h>
#include <jcx/logger/Logger.h>

using namespace jcx;
using namespace logger;

TEST(DateTimeTest, currentDateTime){
    auto now = DateTime::now();
    const char * expect_str = "2017-01-17 10:55:03";
    char buf[128]={0};
    ASSERT_TRUE(now->fill(buf, sizeof(buf)) == (int)strlen(expect_str));
    LOG_INFO("now : %s\n", buf);
}
TEST(DateTimeTest, getString){
    auto now = DateTime::now();
    char buf[128];
    now->fill(buf, 128);
    ASSERT_STREQ(buf, now->getFormatString().get());
    LOG_INFO("now : %s\n", buf);
}
