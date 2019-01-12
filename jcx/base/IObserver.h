
#ifndef  JCX_BASE_IOBSERVER_H
#define  JCX_BASE_IOBSERVER_H

#include "Event.h"

namespace jcx {
namespace base {


class IObserver {
public:
    IObserver(){}
    virtual ~IObserver(){}
    virtual int update(const Event * event) = 0;
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_IOBSERVER_H */
