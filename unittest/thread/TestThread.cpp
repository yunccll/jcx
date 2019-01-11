#include "gtest/gtest.h"
#include <jcx/base/Crossplatform.h>
#include <jcx/base/IRunnable.h>
#include <jcx/base/TestState.h>
#include <jcx/thread/Thread.h>

using namespace jcx;
using namespace base;
using namespace thread;

class Runner : public IRunnable{
public:
    static std::shared_ptr<IRunnable> make(TestState  & testState){
        return std::make_shared<Runner>(testState);
    }
    Runner(TestState & testState)
    :_testStates(testState){ 
        _testStates.__set("Runner_constructor;");
    }
    virtual ~Runner(){
        _testStates.__set("Runner_destructor;");
    }
    virtual void run(){
        _testStates.__set("Runner_run;");
    }
private:
    TestState& _testStates;
};

TEST(ThreadTest, easyUse){
    TestState testState;
    {
        auto pir = Runner::make(testState);
        ASSERT_TRUE(testState == "Runner_constructor;");
        auto thread = Thread::make(pir);
        thread->start();
        ASSERT_TRUE(testState == "Runner_constructor;");
        thread->wait();
        ASSERT_TRUE(testState == "Runner_run;");
    }
    ASSERT_TRUE(testState == "Runner_destructor;");
}

class MyThread : public Thread{
public:
    MyThread(TestProcess & process)
    :_process(process){
    }
    virtual ~MyThread(){
    }
    virtual void run(){
        _process.__add("run;");
    }
private:
    TestProcess & _process;
};

TEST(ThreadTest, use){
    TestProcess tp;
    {
        MyThread mt(tp);
        ASSERT_TRUE(tp == "");

        mt.start();
        ASSERT_TRUE(tp == "");
        mt.wait();
    }
    ASSERT_TRUE(tp == "run;");
}
