#include "gtest/gtest.h"
#include "jcx/base/Util.h"
#include "jcx/base/TestCaseHelper.h"

TEST(TestUtil, use){
    {
        const char * expect_str = "chenglun";
        auto ptr = jcx::base::Util::make_shared_array<char>(32);
        int len = strlen(expect_str);
        ptr.get()[len] = 0;

        memcpy(ptr.get(), expect_str, len);
        ASSERT_STREQ(expect_str, ptr.get());
    }
    {
        const int expect_int [] = {0x01, 0x12, 0x34, 0xAE};
        auto ptr = jcx::base::Util::make_shared_array<int>(32);
        memcpy(ptr.get(), expect_int , sizeof(expect_int));
        for( size_t i = 0; i < sizeof(expect_int)/sizeof(int); ++i)
            ASSERT_EQ(expect_int[i], ptr.get()[i]);
    }
}


TEST(TestUtil, useClass){
    {
        size_t sz = 3;
        jcx::base::_Base c;
        auto ptr = jcx::base::Util::make_shared_array<jcx::base::_Base>(sz);
        for(size_t i = 0;  i < sz; ++i){
            ASSERT_FALSE(c == ptr.get()[i]);
        }
    }
}

TEST(TestUtil, usePtr){
    {
        const char * str = "strings";
        const char * expect_ptr_array[] = {str, str, str};
        auto ptr = jcx::base::Util::make_shared_array<const char *>(32);
        memcpy(ptr.get(), expect_ptr_array, sizeof(expect_ptr_array));
        for(size_t i = 0; i < sizeof(expect_ptr_array)/sizeof(const char*); ++i){
            ASSERT_EQ(expect_ptr_array[i], ptr.get()[i]);
        }
    }
}
