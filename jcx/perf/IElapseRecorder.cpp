#include "IElapseRecorder.h"

#include <string>
#include <sstream>

namespace jcx { 
namespace perf {

IElapseRecorder::~IElapseRecorder() {
}

AbstractElapseRecorder::AbstractElapseRecorder()
:_us(0)
{
}
AbstractElapseRecorder::~AbstractElapseRecorder()
{
}

int AbstractElapseRecorder::blockIn(const std::string & name)
{
    _lastts = std::chrono::steady_clock::now();
    return 0;
}
int AbstractElapseRecorder::blockOut(const std::string & name)
{
    auto cur = std::chrono::steady_clock::now();
    _us += std::chrono::duration_cast<std::chrono::microseconds>(cur - _lastts).count();
    return 0;
}


std::string AbstractElapseRecorder::toString() const
{
    std::ostringstream oss; 
    oss << us() << "us";
    return oss.str();
}
} //namespace perf
} //namespace jcx
