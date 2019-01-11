#include "EventObserver.h"

#include <iostream>
#include "Event.h"

namespace jcx {
namespace base {

EventObserver::EventObserver(){
}
EventObserver::~EventObserver(){
}

void EventObserver::update(const Event * event) {
    printf("EventObserver:\n");
    std::cout << event->toString() << std::endl;
}

}   //namespace base
}   //namespace jcx
