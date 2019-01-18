
#ifndef  JCX_BASE_SUBJECTHELPER_H
#define  JCX_BASE_SUBJECTHELPER_H

#include <list>

namespace jcx {
namespace base {


class SubjectHelper {
public:
    // L --> use L* or L ?????
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
    
    //TODO: L --> use L* or L??????
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

        //  C::value_type ; C::iterator; ++it; *it
        template<typename C>
        class Iterator {
        public:
            Iterator(const typename C::iterator & begin, const typename C::iterator & end)
            : _it(begin)
            , _end(end)
            {
            }
            virtual ~Iterator(){
            }

            bool hasNext() {
                return _it != _end;
            }
            
            typename C::value_type next(){
                typename C::value_type  v = *_it;
                ++_it;
                return v;
            }

        private:
            typename C::iterator _it;
            const typename C::iterator _end;
        };

        typedef typename std::list<L *> Container;
        Iterator<Container> iterator(){
            return Iterator<Container>(_ls.begin(), _ls.end());
        }

    private:
        Container _ls;
    };
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_SUBJECTHELPER_H */
