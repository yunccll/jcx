
#ifndef  JCX_BASE_SIMPLECONTAINER_H
#define  JCX_BASE_SIMPLECONTAINER_H

#include <algorithm>
#include <jcx/base/Iterator.h>

namespace jcx {
namespace base {

template<typename Container>
class __Container {
public:
    using T = typename Container::value_type;

    __Container(){}
    virtual ~__Container(){
        clear();
    }

    int insert(const T & t){
        _container.push_back(t);
        return 0;
    }

    void remove(const T & t){
        auto it = std::find(_container.begin(), _container.end(), t);
        if(it != _container.end()){
            _container.erase(it);
        }
    }

    void removeAll(const T & t){
        auto it = std::find(_container.begin(), _container.end(), t);
        while( it != _container.end()){
            it = _container.erase(it);
            it = std::find(it, _container.end(), t);
        }
    }

    void clear(){
        _container.clear();
    }
    unsigned long long size() const {
        return _container.size();
    }

    /*
    int visit(Caller<bool (T*)> cb){
        auto it  = _container.begin();
        for(; it != _container.end(); ++it){
            if(false == cb(*it)){
                return -1;
            }
        }
        return 0;
    }*/

    //typedef typename jcx::base::Iterator<Container> iterator;
    jcx::base::Iterator<Container> iterator() {
        return jcx::base::Iterator<Container>(_container.begin(), _container.end());
    }
        
private:
    Container _container;
};

}   //namespace base
}   //namespace jcx


#include <vector>
namespace jcx {
namespace base {

template<typename T>
using SimpleVector = __Container<typename std::vector<T>>;

}   //namespace base
}   //namespace jcx


#include <list>
namespace jcx {
namespace base {

template<typename T>
using SimpleList = __Container<typename std::list<T>>;
}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_SIMPLECONTAINER_H */
