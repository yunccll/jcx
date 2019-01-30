#include "MultiShotRecorder.h"

#include <sstream>
#include <jcx/perf/MultiRoundElapseRecorder.h>

namespace jcx { 
namespace perf {

MultiShotRecorder::MultiShotRecorder()
:AbstractElapseRecorder()
,_totalUs(0)
{
}
MultiShotRecorder::~MultiShotRecorder()
{
    auto it = _codeBlockIndex.iterator();
    while(it.hasNext()){
        auto & v = it.next();
        delete v;
    }
}

int MultiShotRecorder::blockIn(const std::string & name)
{
    if(_multiCodeBlock.contains(name)){
        return _multiCodeBlock.get(name)->blockIn(name);
    }

    IElapseRecorder * er = new MultiRoundElapseRecorder(name);
    if(er != NULL){
        _multiCodeBlock.insert(name, er);
        _codeBlockIndex.insert(er);
        return er->blockIn(name);
    }
    return -1;
}

int MultiShotRecorder::blockOut(const std::string & name)
{
    if(_multiCodeBlock.contains(name)){
        auto er =  _multiCodeBlock.get(name);
        er->blockOut(name);
        _totalUs += er->us();
        return 0;
    }
    return -1;
}

std::string MultiShotRecorder::toString() const 
{
    std::ostringstream oss;
    oss << "all:" << us() << "us->[";

    auto is = const_cast<MultiShotRecorder*>(this); //NOTE: need const_iterator ?? tmp solution

    auto it = is->_codeBlockIndex.iterator();
    while(it.hasNext()){
        auto & v = it.next();
        oss << v->toString()  << ",";
    }
    oss << "]";
    return oss.str();
}

} //namespace perf
} //namespace jcx
