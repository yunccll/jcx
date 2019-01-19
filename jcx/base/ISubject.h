
#ifndef  ISUBJECT_H
#define  ISUBJECT_H

#include <list>
#include <jcx/base/Macro.h>
#include <jcx/base/IObserver.h>

namespace jcx {
namespace base {

class Event;

class ISubject {

public:
    ISubject(){}
    virtual ~ISubject(){}

    virtual int attach(IObserver * observer) = 0;
    virtual int detach(IObserver * observer) = 0 ;
    virtual int notify(const Event * event) = 0;
private:
    JCX_NO_COPY_CTORS(ISubject); 
};


class AbstractSubject : public ISubject {
public:
    AbstractSubject();
    ~AbstractSubject() override;

    int attach(IObserver * observer) override;
    int detach(IObserver * observer) override;
    int notify(const Event * event) override;

private:
    JCX_NO_COPY_CTORS(AbstractSubject); 
    typedef typename std::list<IObserver*> Container;
    Container _observers;
};

}   //namespace base
}   //namespace jcx

#endif   /* ISUBJECT_H */
