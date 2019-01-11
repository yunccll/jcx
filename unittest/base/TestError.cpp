#include "gtest/gtest.h"

#include <jcx/base/Error.h>
#include "ErrorMap.h"


using jcx::svr::ErrorMap;
using jcx::base::Error;

TEST(ErrorTest, useDefaultErrorMap){
    auto err = Error<>::OK();
    printf("error: %s\n", err.toString().c_str());

    err = Error<>::Failed();
    printf("error: %s\n", err.toString().c_str());
    
    errno = EAGAIN;
    err = Error<>::IOError();
    printf("error: %s\n", err.toString().c_str());
    errno = 0;
    
}

TEST(ErrorTest, useErrorMap){
    auto err = Error<ErrorMap>::OK();
    printf("error: %s\n", err.toString().c_str());

    err = Error<ErrorMap>::Failed();
    printf("error: %s\n", err.toString().c_str());

    err = Error<ErrorMap>(ErrorMap::IdNotExist);
    printf("error: %s\n", err.toString().c_str());

    err = Error<ErrorMap>(ErrorMap::IdNotExist, "hello world");
    printf("error: %s\n", err.toString().c_str());
}
