#include "EventObserver.h"

#include <iostream>
#include "Event.h"

namespace jcx {
namespace base {

EventObserver::EventObserver(){
}
EventObserver::~EventObserver(){
}

int EventObserver::update(const Event * event) {
    printf("EventObserver:\n");
    std::cout << event->toString() << std::endl;
    return 0;
}

}   //namespace base
}   //namespace jcx
