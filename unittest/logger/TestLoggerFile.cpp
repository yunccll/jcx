#include "gtest/gtest.h"
#include <jcx/logger/File.h>

using namespace jcx;
using namespace logger;

TEST(FileTest, openClose){
    const char * fn = "open_close_except.log";
    {
        File r(fn);
        ASSERT_STREQ(fn, r.getPath());

        ASSERT_FALSE(r.isOpen());
        ASSERT_EQ(0, r.open());
        ASSERT_TRUE(r.isOpen());

        ASSERT_TRUE(File::isExisting(fn));

        ASSERT_EQ(0, r.open()); //open && open 
        ASSERT_TRUE(r.isOpen());

        ASSERT_EQ(0, r.reset()); // open && reset
        ASSERT_TRUE(r.isOpen());

        ASSERT_EQ(0, r.close()); //open && close
        ASSERT_FALSE(r.isOpen());

        ASSERT_EQ(0, r.close()); //close && close
        ASSERT_FALSE(r.isOpen());

        ASSERT_EQ(0, r.reset()); //close && reset
        ASSERT_TRUE(r.isOpen());

        ASSERT_EQ(0, r.close()); //reset && close it
    }

        File::deleteIt(fn);
        ASSERT_FALSE(File::isExisting(fn));
}

TEST(FileTest, use){
    const char * fn = "use_loggerFile.log";
    {
        File r(fn);
        ASSERT_EQ(0, r.open());

        const char * msg = "hello world\n";
        int expectLen = strlen(msg);
        int wlen = r.write(msg, expectLen);
        ASSERT_EQ(expectLen, wlen);

        msg = "another string\n";
        expectLen = strlen(msg);
        wlen = r.write(msg, expectLen);
        ASSERT_EQ(expectLen, wlen);

        ASSERT_EQ(0, r.close());
    }

    File::deleteIt(fn);
    ASSERT_FALSE(File::isExisting(fn));
}

