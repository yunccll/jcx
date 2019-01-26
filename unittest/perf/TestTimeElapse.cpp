#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <sstream>
#include <jcx/base/DateTime.h>
#include <jcx/base/HashMap.h>


#include <chrono>

using namespace std;

class IElapseRecorder {
public:
    virtual ~IElapseRecorder() {}

    virtual int blockIn(const std::string & name) = 0;
    virtual int blockOut(const std::string & name) = 0;

    virtual std::string toString() const  = 0;

    double seconds() const {
        return us()/(1000000.0);
    }
    virtual unsigned long long us() const = 0;
};

class AbstractElapseRecorder : public IElapseRecorder {
public:
    AbstractElapseRecorder()
    :_us(0)
    {
    }
    ~AbstractElapseRecorder() override 
    {
    }

    int blockIn(const std::string & name) override {
        _lastts = std::chrono::steady_clock::now();
        return 0;
    }
    int blockOut(const std::string & name) override {
        auto cur = std::chrono::steady_clock::now();
        _us += std::chrono::duration_cast<std::chrono::microseconds>(cur - _lastts).count();
        return 0;
    }
    unsigned long long us() const override {
        return _us;
    }

    std::string toString() const override {
        ostringstream oss; 
        oss << "sp:"<< us() << "us";
        return oss.str();
    }

protected:
    std::chrono::steady_clock::time_point _lastts;
    unsigned long long _us;
};



class OneShotRecorder : public AbstractElapseRecorder {
public:
    OneShotRecorder()
    :_recorded(false)
    {
    }
    ~OneShotRecorder() override 
    {
    }

    int blockIn(const std::string & name) override {
        if(_recorded == false){
            return AbstractElapseRecorder::blockIn(name);
        }
        return -1;
    }
    int blockOut(const std::string & name) override {
        if(_recorded == false){
            _recorded = true;
            return AbstractElapseRecorder::blockOut(name) ;
        }
        return -1;
    }
    std::string toString() const override {
        ostringstream oss; 
        oss << "c:" << (_recorded == false ? 0 : 1) << "," << AbstractElapseRecorder::toString() ;
        return oss.str();
    }
private:
    bool _recorded;
};

class MultiRoundElapseRecorder : public AbstractElapseRecorder {
public:
    MultiRoundElapseRecorder()
    :_rounds(0)
    {
    }
    ~MultiRoundElapseRecorder() override {
    }
    int blockIn(const std::string & name) override {
        return AbstractElapseRecorder::blockIn(name);
    }
    int blockOut(const std::string & name) override {
        ++ _rounds;
        return AbstractElapseRecorder::blockOut(name) ;
    }
    
    std::string toString() const override {
        ostringstream oss; 
        oss << "c:" << _rounds << "," << AbstractElapseRecorder::toString() ;
        return oss.str();
    }
    
    unsigned long long rounds() const {
        return _rounds;
    }
private:
    unsigned long long _rounds;
};


class MultiShotRecorder : public AbstractElapseRecorder {
public:
    MultiShotRecorder()
    :AbstractElapseRecorder()
    {
    }
    ~MultiShotRecorder() override 
    {
        //TODO: free HashPtr???????
    }

    int blockIn(const std::string & name) override {
        //TODO:  insert or replace  MultiRoundElapseRecorder
        IElapseRecorder * er = new MultiRoundElapseRecorder();
        er->blockIn(name);
        return 0;
        
    }
    int blockOut(const std::string & name) override {
        //TODO: insert or failed RoundRecorder
        IElapseRecorder * er = new MultiRoundElapseRecorder();
        er->blockOut(name);
        //TODO: total elapse -->>>>
        return 0;
    }

    std::string toString() const override {
        ostringstream oss;
        oss << "MultiShotRecorder";
        return oss.str();
    }
private:    
    jcx::base::HashMapForPtr<IElapseRecorder> multiCodeBlock;
};



class CodeBlock final{
public:
    CodeBlock(IElapseRecorder & elapseRecorder)
    : CodeBlock(elapseRecorder, "")
    {
    }
    CodeBlock(IElapseRecorder & elapseRecorder, const char * name)
    : _elapseRecorder(elapseRecorder)
    , _name(name)
    {
        _elapseRecorder.blockIn(_name);
    }
    ~CodeBlock(){
        _elapseRecorder.blockOut(_name);
    }

    const std::string & name(){
        return _name;
    }
private:
    IElapseRecorder & _elapseRecorder;
    std::string _name;
};

TEST(TimeElapseTest, use){

    OneShotRecorder er;
    {
        CodeBlock cb(er, "forLoop");
        usleep(5000); //5ms
    }
    std::cout << er.toString() << std::endl;
}


TEST(TimeElapseTest, MultiRoundElapseRecorder){
    MultiRoundElapseRecorder er ; 
    {
        CodeBlock cb(er, "name1");
        for( int i = 0; i < 10 ;  ++i){
            {
                CodeBlock cb(er, "loop_i");
                usleep(3000);//3ms
            }
        }
    }
    ASSERT_TRUE(11 == er.rounds());
    std::cout << er.toString() << std::endl;
}

TEST(TimeElapseTest, MultiShotRecorder){
    MultiShotRecorder er ; 
    {
        CodeBlock cb(er, "name1");
        for( int i = 0; i < 10 ;  ++i){
            {
                CodeBlock cb(er, "loop_i");
                usleep(3000);//3ms

                for( int j = 0 ; j < 22; ++j){
                    CodeBlock jloop(er, "loop_j");
                    usleep(1000); //1ms
                }
            }
        }
    }
    std::cout << er.toString() << std::endl;
}
