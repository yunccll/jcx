#include "Event.h"

#include <sstream>


namespace jcx {
namespace base {

Event::Event(const int id, void * arg)
:_id(id)
,_arg(arg)
{
}

Event::~Event(){}
std::string Event::toString() const {
    std::ostringstream ss;
    ss << "Event: id:" << _id 
        << ", arg: " << (unsigned long)_arg;
    return ss.str();
}

}   //namespace base
}   //namespace jcx
