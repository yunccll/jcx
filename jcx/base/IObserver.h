
#ifndef  IOBSERVER_H
#define  IOBSERVER_H

#include "Event.h"

namespace jcx {
namespace base {


class IObserver {
public:
    IObserver(){}
    virtual ~IObserver(){}
    virtual void update(const Event * event) = 0;
};

}   //namespace base
}   //namespace jcx

#endif   /* IOBSERVER_H */
