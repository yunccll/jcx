
#ifndef  EVENTSUBJECT_H
#define  EVENTSUBJECT_H

#include "ISubject.h"

namespace jcx {
namespace base {

class Event;
class EventSubject : public AbstractSubject {
public:
    EventSubject();
    virtual ~EventSubject();
    
    virtual int emit(const Event * event);

private:
};

}   //namespace base
}   //namespace jcx

#endif   /* EVENTSUBJECT_H */
