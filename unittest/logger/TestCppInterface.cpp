#include "gtest/gtest.h"
#include <jcx/base/CrossPlatform.h>

#define LOG  std::cout

TEST(CppInterface, use){
    LOG << "" << std::endl;
    LOG << int(12) << std::endl;
    LOG << float(12) << std::endl;
    LOG << double(12) << std::endl;
    LOG << std::string("hshshshsh") << std::endl;
}
