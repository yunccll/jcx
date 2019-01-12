#include "Event.h"

#include <sstream>

//#include <iostream> //for test


namespace jcx {
namespace base {

Event::Event(const int id, void * arg)
:_id(id)
,_arg(arg)
{
 //   std::cout << "Event constructor : "  << _id << std::endl;
}

Event::~Event(){
  //  std::cout << "Event destructor : "  << _id << std::endl;
}
std::string Event::toString() const {
    std::ostringstream ss;
    ss << "Event: id:" << _id 
        << ", arg: " << (unsigned long)_arg;
    return ss.str();
}

}   //namespace base
}   //namespace jcx
