
#ifndef  JCX_BASE_EVENTOBSERVER_H
#define  JCX_BASE_EVENTOBSERVER_H

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

#endif   /* JCX_BASE_EVENTOBSERVER_H */
