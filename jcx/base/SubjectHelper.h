
#ifndef  JCX_BASE_SUBJECTHELPER_H
#define  JCX_BASE_SUBJECTHELPER_H

#include <list>

namespace jcx {
namespace base {


class SubjectHelper {
public:
    template<typename L, typename T>
    class One {
    public:
        One(L* l)
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
        L * _l;
    };
    
    template<typename L, typename T>
    class Many {
    public:
        virtual ~Many(){
        }

        T& attach(L * l){
            if(l){
                _ls.push_back(l);
            }
            return static_cast<T&>(*this);
        }
        T& detach(L *l){
            if(l){
                _ls.remove(l);
            }
            return static_cast<T&>(*this);
        }

        typedef typename std::list<L*> container;
        typename container::iterator begin(){
            return _ls.begin();
        }
        typename container::iterator end(){
            return _ls.end();
        }
        
    private:
        container _ls;
    };
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_SUBJECTHELPER_H */
