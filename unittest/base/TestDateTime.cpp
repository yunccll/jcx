#include "gtest/gtest.h"

#include <jcx/base/Crossplatform.h>
#include <jcx/base/DateTime.h>

#include <jcx/logger/LoggerProxy.h>

using namespace std;
using namespace jcx;
using namespace base;

TEST(DateTimeTest, fromExcept){
    auto tm = DateTime::from("");
    ASSERT_TRUE(tm == 0);

    tm = DateTime::from(0);
    ASSERT_TRUE(tm == 0);
}
TEST(DateTimeTest, fromDefaultFmt){
    auto str ="2017-02-05 23:25:43";
    auto tm = DateTime::from(str);
    ASSERT_STREQ(str, tm->str().get());

    str ="2017-02-05 23:25";
    tm = DateTime::from(str);
    ASSERT_TRUE(tm == 0);
}

TEST(DateTimeTest, fromFmt){
    auto str = "2017-02-05";
    auto tm = DateTime::from(str, "%Y-%m-%d");
    ASSERT_TRUE(tm != 0);
    auto expect_str = "2017-02-05 00:00:00";
    ASSERT_STREQ(expect_str, tm->str().get());
}

TEST(DateTimeTest, make){
    auto now = DateTime::now();
    
    auto copy_now = DateTime::make(now);
    ASSERT_TRUE(*copy_now == now);
    ASSERT_STREQ(now.str().get(), copy_now->str().get());
}

TEST(DateTimeTest, use){

    auto dt = DateTime::make();
    const char * tm_1970 = "1970-01-01 08:00:00";
    ASSERT_STREQ(tm_1970, dt->str().get());


    auto now = DateTime::now();
    {
        auto newDateTime = DateTime::make();
        *newDateTime  = now;
        ASSERT_TRUE(*newDateTime == now);
        ASSERT_STREQ(newDateTime->str().get(), now.str().get());

        unsigned long long sec = DateTime::Year(1).seconds();
        *newDateTime  += DateTime::Year();
        ASSERT_EQ(sec, (*newDateTime - now));

        sec += DateTime::Day(1).seconds();
        *newDateTime  += DateTime::Day();
        ASSERT_EQ(sec, *newDateTime - now);

        sec += DateTime::Hour(1).seconds();
        *newDateTime  += DateTime::Hour();
        ASSERT_EQ(sec, *newDateTime - now);

        sec += DateTime::Minute(1).seconds();
        *newDateTime  += DateTime::Minute();
        ASSERT_EQ(sec, *newDateTime - now);

        sec += DateTime::Second(1).seconds();
        *newDateTime  += DateTime::Second();
        ASSERT_EQ(sec, *newDateTime - now);
    }
    {
        auto newDateTime = DateTime::make();
        *newDateTime  = now;

        unsigned long long sec = DateTime::Year(1).seconds();
        DateTime::Year() += *newDateTime;
        ASSERT_EQ(sec, (*newDateTime - now));

        sec += DateTime::Day(1).seconds();
        DateTime::Day() += *newDateTime;
        ASSERT_EQ(sec, *newDateTime - now);

        sec += DateTime::Hour(1).seconds();
        DateTime::Hour() += *newDateTime;
        ASSERT_EQ(sec, *newDateTime - now);

        sec += DateTime::Minute(1).seconds();
        DateTime::Minute() += *newDateTime;
        ASSERT_EQ(sec, *newDateTime - now);

        sec += DateTime::Second(1).seconds();
        DateTime::Second() += *newDateTime;
        ASSERT_EQ(sec, *newDateTime - now);
    }
}

TEST(DateTimeTest, addSub){
    auto now = DateTime::now();

    auto zero = DateTime::make();
    *zero = now;

    auto added = DateTime::make();
    *added = now + DateTime::Hour(1);
    ASSERT_STREQ(added->str().get(), (now + DateTime::Hour(1)).str().get());

    auto subed = DateTime::make();
    *subed = now - DateTime::Hour(1);
    ASSERT_STREQ(subed->str().get(), (now - DateTime::Hour(1)).str().get());
}

TEST(DateTimeTest, equal){
    auto now = DateTime::now();
    ASSERT_TRUE(now == now);
    
    auto zero = DateTime::make();
    ASSERT_FALSE(now == *zero);
    ASSERT_TRUE(now != *zero);
}

TEST(DateTimeTest, equalOperator){
    auto first = DateTime::now();
    auto second = DateTime::now() - DateTime::Hour(1);

    std::cout << second - first << std::endl;

}
