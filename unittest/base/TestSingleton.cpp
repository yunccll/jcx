#include "gtest/gtest.h"
#include <jcx/base/Crossplatform.h>
#include <jcx/base/Singleton.h>

using namespace jcx;
using namespace base;

class SingletonTest : public Singleton<SingletonTest>{
private:
    SingletonTest(){}
public:
    virtual ~SingletonTest(){}
    void append(int i){ _str += std::to_string(i);}
    std::string & str(){return _str;}
private:
    std::string _str;

    SINGLETON(SingletonTest);
};

TEST(SingletonTemplateTest, use){
    void * inst = SingletonTest::instance();
    ASSERT_TRUE(inst == SingletonTest::instance());

    SingletonTest::instance()->append(1);
    ASSERT_TRUE(std::string("1") == SingletonTest::instance()->str());
    SingletonTest::instance()->append(2);
    ASSERT_TRUE(std::string("12")== SingletonTest::instance()->str());
}

class Obj {
    Obj(){
        printf("constructor obj\n");
    }
public:
    ~Obj(){
        printf("destructor obj\n");
    }
    void print(){printf("ok\n");}
    const char * get(){return _str.c_str();}
    void  append(const char * val ) {_str += val; }

private:
    std::string _str;
    friend Singleton<Obj>;
};

TEST(SingletonTest, use){
    const char * expect = "12";
    Singleton<Obj>::instance()->append(expect);
    ASSERT_STREQ(expect, Singleton<Obj>::instance()->get());
}
