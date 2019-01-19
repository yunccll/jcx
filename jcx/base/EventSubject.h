
#ifndef  JCX_BASE_EVENTSUBJECT_H
#define  JCX_BASE_EVENTSUBJECT_H

#include <jcx/base/Macro.h>
#include <jcx/base/ISubject.h>

namespace jcx {
namespace base {

class Event;
class EventSubject : public AbstractSubject {
public:
    EventSubject();
    ~EventSubject() override;
    
    virtual int emit(const Event * event);
private:
    JCX_NO_COPY_CTORS(EventSubject);
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_EVENTSUBJECT_H */
