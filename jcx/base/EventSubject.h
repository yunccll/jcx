
#ifndef  JCX_BASE_EVENTSUBJECT_H
#define  JCX_BASE_EVENTSUBJECT_H

#include "ISubject.h"

namespace jcx {
namespace base {

class Event;
class EventSubject : public AbstractSubject {
public:
    EventSubject();
    ~EventSubject() override;
    
    virtual int emit(const Event * event);
private:
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_EVENTSUBJECT_H */
