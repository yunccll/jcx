
#ifndef  JCX_PERF_MULTISHOTRECORDER_H
#define  JCX_PERF_MULTISHOTRECORDER_H

#include <string>
#include <jcx/base/HashMap.h>
#include <jcx/base/SimpleContainer.h>
#include <jcx/perf/IElapseRecorder.h>

namespace jcx { 
namespace perf {

class MultiShotRecorder : public AbstractElapseRecorder {
public:
    MultiShotRecorder();
    ~MultiShotRecorder() override ;

    int blockIn(const std::string & name) override ;

    int blockOut(const std::string & name) override ;

    unsigned long long us() const override {
        return _totalUs;
    }

    std::string toString() const override ;

private:    
    jcx::base::HashMapForPtr<IElapseRecorder> _multiCodeBlock;
    jcx::base::SimpleVector<IElapseRecorder*> _codeBlockIndex;
    unsigned long long _totalUs;
};

} //namespace perf
} //namespace jcx

#endif   /* JCX_PERF_MULTISHOTRECORDER_H */
