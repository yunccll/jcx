#include "gtest/gtest.h"

#include <jcx/base/TestState.h>
#include <memory>

using namespace jcx;
using namespace base;

TEST(TestStateTest, use){
    TestState state;
    state.__set(1);
    ASSERT_TRUE(state == "1");

    state.__set("12345");
    ASSERT_TRUE(state == "12345");
}


class TestStateSub :  public TestState{
public:
    TestStateSub(){
        TestState::__set("constructor");
    }
    ~TestStateSub(){
        TestState::__set("destructor");
    }
    void run(){
        TestState::__set("run");
    }
};
TEST(TestStateTest, useClass){
    TestStateSub tss;
    ASSERT_TRUE(tss == "constructor");
    tss.run();
    ASSERT_TRUE(tss == "run");
    //can not test the destructor
}

class TestStateSub2 {
public:
    static std::shared_ptr<TestStateSub2> make(TestState & testState){
        return std::make_shared<TestStateSub2>(testState);
    }
    TestStateSub2(TestState & testState)
    :_testStates(testState){ 
        _testStates.__set("constructor;");
    }
    ~TestStateSub2(){
        _testStates.__set("destructor;");
    }
    void run(){
        _testStates.__set("run;");
    }
private:
    TestState& _testStates;
};

TEST(TestStateTest, injectUse){
    TestState testState;
    {
        auto pir = TestStateSub2::make(testState);
        ASSERT_TRUE(testState == "constructor;");
        pir->run();
        ASSERT_TRUE(testState == "run;");
    }
    ASSERT_TRUE(testState == "destructor;");
}
