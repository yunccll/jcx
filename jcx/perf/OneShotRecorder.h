
#ifndef  JCX_PERF_ONESHOTRECORDER_H
#define  JCX_PERF_ONESHOTRECORDER_H

#include <jcx/perf/IElapseRecorder.h>

namespace jcx { 
namespace perf {

class OneShotRecorder : public AbstractElapseRecorder {
public:
    OneShotRecorder();
    ~OneShotRecorder() override ;

    int blockIn(const std::string & name) override ;
    int blockOut(const std::string & name) override ;

    std::string toString() const override ;

private:
    bool _recorded;
};

} //namespace perf
} //namespace jcx

#endif   /* JCX_PERF_ONESHOTRECORDER_H */
