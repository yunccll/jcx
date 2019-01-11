#include "gtest/gtest.h"

#include <jcx/base/TestState.h>
#include <memory>

using namespace jcx;
using namespace base;

TEST(TestProcessTest, easyUse){
    TestProcess state;
    state.__set(1);
    ASSERT_TRUE(state == "1");

    state.__set("12345");
    ASSERT_TRUE(state == "12345");
}

class TestProcessSub {
public:
    static std::shared_ptr<TestProcessSub> make(TestProcess & testProcess){
        return std::make_shared<TestProcessSub>(testProcess);
    }
    TestProcessSub(TestProcess & testProcess)
    :_testProcesss(testProcess){ 
        _testProcesss.__add("constructor;");
    }
    ~TestProcessSub(){
        _testProcesss.__add("destructor;");
    }
    void run(){
        _testProcesss.__add("run;");
    }
private:
    TestProcess& _testProcesss;
};

TEST(TestProcessTest, use){
    TestProcess  proc;
    { 
        TestProcessSub tps(proc);
        tps.run();
    }
    ASSERT_TRUE(proc[0] =="constructor;");
    ASSERT_TRUE(proc[1] =="run;");
    ASSERT_TRUE(proc[2] =="destructor;");
    ASSERT_TRUE(proc == "constructor;run;destructor;");
}

class TestProcessSub2 {
public:
    static std::shared_ptr<TestProcessSub2> make(TestProcess & testProcess){
        return std::make_shared<TestProcessSub2>(testProcess);
    }
    TestProcessSub2(TestProcess & testProcess)
    :_testProcesss(testProcess){ 
        _testProcesss.__set("constructor;");
    }
    ~TestProcessSub2(){
        _testProcesss.__set("destructor;");
    }
    void run(){
        _testProcesss.__set("run;");
    }
private:
    TestProcess& _testProcesss;
};

TEST(TestProcessTest, injectUse){
    TestProcess testProcess;
    {
        auto pir = TestProcessSub2::make(testProcess);
        ASSERT_TRUE(testProcess == "constructor;");
        pir->run();
        ASSERT_TRUE(testProcess == "run;");
    }
    ASSERT_TRUE(testProcess == "destructor;");
}
