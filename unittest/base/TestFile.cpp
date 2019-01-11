#include "gtest/gtest.h"
#include <jcx/base/File.h>

using namespace jcx;
using namespace base;


TEST(FileTest, deleteNothing){
    const char * fn = "_XX_a.txt";
    ASSERT_FALSE(File::isExisting(fn));
    File::deleteIt(fn);
    ASSERT_FALSE(File::isExisting(fn));
}

TEST(FileTest, create){
    const char * fn = "__a.txt";
    File::deleteIt(fn);
    ASSERT_FALSE(File::isExisting(fn));

    ASSERT_EQ(0, File::create(fn));
    ASSERT_TRUE(File::isExisting(fn));

    File::deleteIt(fn);
    ASSERT_FALSE(File::isExisting(fn));
}

/* TODO: another create
TEST(FileTest, create){
    const char * fn =  "__a.txt";
    F r(fn, CREATE);
    r.close();
    ASSERT_TRUE(File::isExisting(fn));
    File::deleteIt(fn);
    ASSERT_FALSE(File::isExisting(fn));
}
//TODO: modify
TEST(FileTest, modify){
    const char * fn =  "__a.txt";
    File::deleteIt(fn);
    ASSERT_FALSE(File::isExisting(fn));
    ASSERT_EQ(0, File::create(fn));
    ASSERT_TRUE(File::isExisting(fn));

    //modify 
}
*/

//TODO: read write
TEST(FileTest, use){
    const char * fn = "a.txt";
    File r("a.txt");
    ASSERT_STREQ(fn, r.getPath());

    const char * msg = "message";
    int writedLen = r.write(msg);
    ASSERT_TRUE(writedLen >= 0);

    char buf[128];
    int readLen = r.read(buf, sizeof(buf));
    ASSERT_EQ(writedLen, readLen);
    //auto msg = r.read();
}

TEST(FileTest, currentWorkingDirectory){
    auto cwd = File::getcwd();
    printf("cwd:%s\n", cwd.get());
    ASSERT_TRUE(cwd != NULL);
    ASSERT_TRUE(strlen(cwd.get()) > 0);
}

