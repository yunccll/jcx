
#ifndef  ISUBJECT_H
#define  ISUBJECT_H

#include <list>
#include"IObserver.h"

#include <cstdio>

namespace jcx {
namespace base {

class Event;

class ISubject {

public:
    virtual ~ISubject(){}

    virtual int attach(IObserver * observer) = 0;
    virtual int detach(IObserver * observer) = 0 ;
    virtual int notify(const Event * event) = 0;

};


class AbstractSubject : public ISubject {
public:
    virtual ~AbstractSubject();

    virtual int attach(IObserver * observer);
    virtual int detach(IObserver * observer);
    virtual int notify(const Event * event);

private:
    std::list<IObserver*> _observers;
};

}   //namespace base
}   //namespace jcx

#endif   /* ISUBJECT_H */
