#include "OneShotRecorder.h"

#include <string>
#include <sstream>

namespace jcx { 
namespace perf {

OneShotRecorder::OneShotRecorder()
:_recorded(false)
{
}

OneShotRecorder::~OneShotRecorder()
{
}

int OneShotRecorder::blockIn(const std::string & name)
{
    if(_recorded == false){
        return AbstractElapseRecorder::blockIn(name);
    }
    return -1;
}

int OneShotRecorder::blockOut(const std::string & name)
{
    if(_recorded == false){
        _recorded = true;
        return AbstractElapseRecorder::blockOut(name) ;
    }
    return -1;
}

std::string OneShotRecorder::toString() const 
{
    std::ostringstream oss; 
    oss << "c:" << (_recorded == false ? 0 : 1) << "," << AbstractElapseRecorder::toString() ;
    return oss.str();
}

} //namespace perf
} //namespace jcx
