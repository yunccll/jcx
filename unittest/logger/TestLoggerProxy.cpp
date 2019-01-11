#include "gtest/gtest.h"
#include <jcx/logger/Logger.h>
#include <jcx/logger/Factory.h>
#include <jcx/thread/Thread.h>

using namespace jcx;
using namespace logger;
using namespace base;
using namespace thread;

//TODO: LoggerProxy mock test

TEST(LoggerProxyTest, defaultFactory){
    //use DefaultLogger
    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "illllllll");
    LOG_FLUSH();
}


TEST(LoggerProxyTest, useStdout){
    LoggerProxy::instance()->setFactory(new StdoutFactory());
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);

    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "illllllll");

}

TEST(LoggerProxyTest, resetLoggerFactor){
    //default logger
    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "illllllll");

    //default logger again
    LoggerProxy::instance()->setFactory(NULL);
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);
    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "illllllll");

    //use stdin logger
    LoggerProxy::instance()->setFactory(new StdoutFactory());
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);
    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "illllllll");

    LoggerProxy::instance()->setFactory(new StdoutFactory());
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);
    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "illllllll");

    LoggerProxy::instance()->setFactory(NULL);
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);
    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "illllllll");
}



#include <jcx/base/IRunnable.h>
#include <jcx/thread/Thread.h>
class TestLoggerRunner : public IRunnable{
public:

    TestLoggerRunner(){}
    virtual ~TestLoggerRunner(){}
    virtual void run(){
        LOG_INFO("%s, %lu\n", "hello", Thread::id());
        LOG_DEBUG("%s, %lu\n", "hello", Thread::id());
        LOG_WARN("%s, %lu\n", "hello", Thread::id());
        LOG_ERROR("%s, %lu\n", "hello", Thread::id());
        LOG_FLUSH();
    }
};
TEST(LoggerProxyTest, multiThreaduse){
    LoggerProxy::instance()->setFactory(new FileLoggerFactory("file"));
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);

    auto runner = std::make_shared<TestLoggerRunner>();

    const int thread_len = 100;
    std::shared_ptr<Thread> tarr[thread_len];
    for( int i = 0 ; i < thread_len; ++i){
        tarr[i] = Thread::make(runner);
        tarr[i]->start();
    }
    for(int i =0; i < thread_len; ++i){
        tarr[i]->wait();
    }
}

TEST(LoggerProxyTest, setLevel){
    LoggerProxy::instance()->setFactory(NULL);
    LoggerProxy::instance()->setLevel(LogLevel::ERROR);
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::ERROR);
    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "set this level to ERROR");
}

TEST(LoggerProxyTest, fileLogger){
    LoggerProxy::instance()->setFactory(new FileLoggerFactory("main"));
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);
    LOG_INFO("%s, %d, %f\n","msg", 123, 3444.44444);
    LOG_DEBUG("%s %04d\n", "ptr is ", 0);
    LOG_WARN("%s\n", "hello");
    LOG_ERROR("%s\n", "illllllll");

    LoggerProxy::instance()->setFactory(new FileLoggerFactory("main_block2"));
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);
    int times = 2000;
    for( int i = 0 ; i < times; ++i){
        LOG_INFO("%s\n","msgmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmx");
    }

    LoggerProxy::instance()->setFactory(NULL);
    ASSERT_TRUE(LoggerProxy::instance()->getLevel() == LogLevel::INFO);
}
