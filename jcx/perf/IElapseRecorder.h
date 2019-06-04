
#ifndef  JCX_PERF_IELAPSERECORDER_H
#define  JCX_PERF_IELAPSERECORDER_H


#include <chrono>
#include <string>

namespace jcx { 
namespace perf {

class IElapseRecorder {
public:
    virtual ~IElapseRecorder();

    virtual int blockIn(const std::string & name) = 0;
    virtual int blockOut(const std::string & name) = 0;

    virtual std::string toString() const = 0;

    double seconds() const {
        return us()/(1000000.0);
    }
    virtual unsigned long long us() const = 0;
};


class AbstractElapseRecorder : public IElapseRecorder {
public:
    AbstractElapseRecorder();
    ~AbstractElapseRecorder() override ;

    int blockIn(const std::string & name) override;
    int blockOut(const std::string & name) override;
    unsigned long long us() const override {
        return _us;
    }

    std::string toString() const override ;

protected:
    std::chrono::steady_clock::time_point _lastts;
    unsigned long long _us;
};

} //namespace perf
} //namespace jcx

#endif   /* JCX_PERF_IELAPSERECORDER_H */
