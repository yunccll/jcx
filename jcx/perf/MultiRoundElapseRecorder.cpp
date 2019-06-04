#include "MultiRoundElapseRecorder.h"

#include <sstream>

namespace jcx { 
namespace perf {

MultiRoundElapseRecorder::MultiRoundElapseRecorder(const std::string & name)
:_rounds(0)
,_name(name)
{
}

MultiRoundElapseRecorder::~MultiRoundElapseRecorder()
{
}

int MultiRoundElapseRecorder::blockIn(const std::string & name)
{
    return AbstractElapseRecorder::blockIn(name);
}

int MultiRoundElapseRecorder::blockOut(const std::string & name)
{
    ++ _rounds;
    return AbstractElapseRecorder::blockOut(name) ;
}

std::string MultiRoundElapseRecorder::toString() const
{
    std::ostringstream oss; 
    oss << _name << ":" << _rounds << ":" << AbstractElapseRecorder::toString() ;
    return oss.str();
}

} //namespace perf
} //namespace jcx
