
#ifndef  EVENTOBSERVER_H
#define  EVENTOBSERVER_H

#include "IObserver.h"

namespace jcx {
namespace base {

class Event;

class EventObserver : public IObserver {
public:
    EventObserver();
    virtual ~EventObserver();

    virtual void update(const Event * event) ;
};

}   //namespace base
}   //namespace jcx

#endif   /* EVENTOBSERVER_H */
