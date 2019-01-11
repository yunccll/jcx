#include "gtest/gtest.h"

#include <jcx/base/TestCaseHelper.h>
#include <jcx/base/Crossplatform.h>

using jcx::base::_Base;

std::unique_ptr<_Base> getValue(){
    auto b = std::unique_ptr<_Base>(new _Base);
    return b;
}


TEST(UniquePtrTest, use){
    {
        //case 1.
        auto b = std::unique_ptr<_Base>(new _Base);
    }
    {
        //case 2.
        std::unique_ptr<_Base> pB(new _Base);
    } 
    {
        //case 3.
        auto b = getValue();

    }
    {
        //case 4.
        auto b = std::unique_ptr<_Base>(getValue());
    }
    {
        //case 5.
        auto a = getValue();
        auto b = std::move(a);
    }
    {
        //error case 1.
        //auto b = std::move(getValue());
        
        //auto b = std::unique_ptr<_Base>(new _Base);
        //auto c = b;   //error case 2.
        //auto d(b);    //error case 3.
    }
    
}
