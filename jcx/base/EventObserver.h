
#ifndef  JCX_BASE_EVENTOBSERVER_H
#define  JCX_BASE_EVENTOBSERVER_H

#include <jcx/base/Macro.h>
#include <jcx/base/IObserver.h>

namespace jcx {
namespace base {

class Event;

class EventObserver : public IObserver {
public:
    EventObserver();
    ~EventObserver() override;

    int update(const Event * event) override;
private:
    JCX_NO_COPY_CTORS(EventObserver);
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_EVENTOBSERVER_H */
