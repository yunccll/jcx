#include "EventSubject.h"

#include "Event.h"

namespace jcx {
namespace base {

EventSubject::EventSubject(){
}
EventSubject::~EventSubject(){
}

int EventSubject::emit(const Event * event){
    return notify(event);
}

}   //namespace base
}   //namespace jcx
