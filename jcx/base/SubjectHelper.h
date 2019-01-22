
#ifndef  JCX_BASE_SUBJECTHELPER_H
#define  JCX_BASE_SUBJECTHELPER_H

#include <jcx/base/Macro.h>
#include <jcx/base/SimpleContainer.h>

namespace jcx {
namespace base {

class SubjectHelper {
public:
    template<typename L, typename T>
    class One {
    public:
        One()
        :_l(NULL){
        }
        One(L * l)
        :_l(l){
        }
        virtual ~One(){
        }
        
        L * getListener() const{
            return _l;
        }

        T& attach(L * l){
            if(l != NULL && l != _l){
                _l = l;
            }
            return static_cast<T&>(*this);
        }
        T& detach(){
            _l = NULL;
            return static_cast<T&>(*this);
        }

    private:
        JCX_NO_COPY_CTORS(One);
        L * _l;
    };
    
    template<typename L, typename T>
    class Many {
    public:
        Many(){}
        virtual ~Many(){
        }

        T& attach(L* l){
            if(l){
                _ls.insert(l);
            }
            return static_cast<T&>(*this);
        }
        T& detach(L* l){
            if(l){
                _ls.remove(l);
            }
            return static_cast<T&>(*this);
        }

    protected:
        auto iterator(){
            return _ls.iterator();
        }
    private:
        JCX_NO_COPY_CTORS(Many);
        SimpleVector<L*> _ls;
    };
};


}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_SUBJECTHELPER_H */
