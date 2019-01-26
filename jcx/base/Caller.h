
#ifndef  JCX_BASE_CALLER_H
#define  JCX_BASE_CALLER_H

#include <jcx/base/Macro.h>



namespace jcx {
namespace base {

/*  
 *  Deprecated
 *  */
template<typename R>
struct Caller{
    typedef R (*f_t)(void);
    Caller(const f_t & f)
    :_f(f)
    {
    }
    ~Caller(){
    }

    R operator () (void){
        return _f();
    }
private:
    JCX_NO_DEFAULT_CTORS(Caller);
    f_t _f;
};

template<typename R, typename A1>
struct Caller <R (A1)>{
    typedef R (*f_t)(A1);
    Caller(const f_t & f)
    :_f(f)
    {
    }
    ~Caller(){
    }
    R operator () (const A1 & a1){
        return _f(a1);
    }
private:
    JCX_NO_DEFAULT_CTORS(Caller);
    f_t _f;
};

template<typename R, typename A1, typename A2>
struct Caller<R (A1, A2)>{
    typedef R (*f_t)(A1, A2);
    Caller(const f_t & f)
    :_f(f)
    {
    }
    ~Caller(){
    }
    R operator () (const A1 & a1, const A2 & a2){
        return _f(a1, a2);
    }
private:
    JCX_NO_DEFAULT_CTORS(Caller);
    f_t _f;
};

template<typename R, typename A1, typename A2, typename A3>
struct Caller< R (A1, A2, A3)>{
    typedef R (*f_t)(A1, A2, A3);
    Caller(const f_t & f)
    :_f(f)
    {
    }
    ~Caller(){
    }
    R operator () (const A1 & a1, const A2 & a2, const A3 & a3){
        return _f(a1, a2, a3);
    }
private:
    JCX_NO_DEFAULT_CTORS(Caller);
    f_t _f;
};

template<typename R, typename A1, typename A2, typename A3, typename A4>
struct Caller< R (A1, A2, A3, A4)>{
    typedef R (*f_t)(A1, A2, A3, A4);
    Caller(const f_t & f)
    :_f(f)
    {
    }
    ~Caller(){
    }
    R operator () (const A1 & a1, const A2 & a2, const A3 & a3, const A4 & a4){
        return _f(a1, a2, a3, a4);
    }
private:
    JCX_NO_DEFAULT_CTORS(Caller);
    f_t _f;
};

} //namespace base
} //namespace jcx

#endif   /* JCX_BASE_CALLER_H */
