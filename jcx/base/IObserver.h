
#ifndef  JCX_BASE_IOBSERVER_H
#define  JCX_BASE_IOBSERVER_H

#include <jcx/base/Macro.h>

namespace jcx {
namespace base {


class Event;
class IObserver {
public:
    IObserver(){}
    virtual ~IObserver(){}
    virtual int update(const Event * event) = 0;
private:
    JCX_NO_COPY_CTORS(IObserver); 
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_IOBSERVER_H */
