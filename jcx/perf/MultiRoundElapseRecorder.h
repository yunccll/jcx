
#ifndef  JCX_PERF_MULTIROUNDELAPSERECORDER_H
#define  JCX_PERF_MULTIROUNDELAPSERECORDER_H

#include <string>
#include <jcx/perf/IElapseRecorder.h>

namespace jcx { 
namespace perf {


class MultiRoundElapseRecorder : public AbstractElapseRecorder {
public:
    MultiRoundElapseRecorder(const std::string & name);
    ~MultiRoundElapseRecorder() override ;
    int blockIn(const std::string & name) override ;
    int blockOut(const std::string & name) override ;
    
    std::string toString() const override ;
    
    unsigned long long rounds() const {
        return _rounds;
    }
private:
    unsigned long long _rounds;
    std::string _name;
};

} //namespace perf
} //namespace jcx

#endif   /* JCX_PERF_MULTIROUNDELAPSERECORDER_H */
