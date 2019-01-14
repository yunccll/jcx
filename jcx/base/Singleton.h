#ifndef  JCX_BASE_SINGLETON_H
#define  JCX_BASE_SINGLETON_H

namespace jcx { 
namespace base {

template <typename T>
class Singleton{
public:
    Singleton(){}
    virtual ~Singleton(){}

    static T * instance(){
        static T t;
        _obj.do_nothing();
        return &t;
    }

private:
    struct create_obj {
        create_obj(){
            Singleton <T>::instance();
        }
        inline void do_nothing() const {}
    };
    static create_obj _obj;
};
template <typename T> typename Singleton<T>::create_obj Singleton<T>::_obj;

#define SINGLETON(T)    friend Singleton<T>

} //namespace base
} //namespace jcx

#endif   /* JCX_BASE_SINGLETON_H */
