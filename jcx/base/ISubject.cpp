#include "ISubject.h"

namespace jcx {
namespace base {

AbstractSubject::AbstractSubject(){
}
AbstractSubject::~AbstractSubject(){
}

int AbstractSubject::attach(IObserver * observer){
    if(observer){
        _observers.insert(observer);
        return 0;
    }
    return -1;
}
int AbstractSubject::detach(IObserver * observer){
    if(observer){
        _observers.remove(observer);
        return 0;
    }
    return -1;
}

int AbstractSubject::notify(const Event * event){
    if(event){
        auto it = _observers.iterator();
        while(it.hasNext()){
            it.next()->update(event);
        }
        return 0;
    }
    return -1;
}

}   //namespace base
}   //namespace jcx
