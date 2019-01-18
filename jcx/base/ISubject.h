
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

    //TODO: const ???
    virtual int attach(IObserver * observer) = 0;
    virtual int detach(IObserver * observer) = 0 ;
    virtual int notify(const Event * event) = 0;
};


class AbstractSubject : public ISubject {
public:
    ~AbstractSubject() override;

    int attach(IObserver * observer) override;
    int detach(IObserver * observer) override;
    int notify(const Event * event) override;

private:
    std::list<IObserver*> _observers;
};

}   //namespace base
}   //namespace jcx

#endif   /* ISUBJECT_H */
