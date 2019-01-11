#include "ISubject.h"

namespace jcx {
namespace base {

AbstractSubject::~AbstractSubject(){
}

int AbstractSubject::attach(IObserver * observer){
    if(observer){
        _observers.push_back(observer);
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
        std::list<IObserver *>::iterator it = _observers.begin();
        for(; it != _observers.end(); ++it){
            (*it)->update(event);
        }
        return 0;
    }
    return -1;
}

}   //namespace base
}   //namespace jcx
