
#ifndef  JCX_BASE_CALLER_H
#define  JCX_BASE_CALLER_H

namespace jcx {
namespace base {


//TODO:  A1  A2 A3 type ==> const A1 & ?????

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
    R operator () (A1 a1){
        return _f(a1);
    }
private:
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
    R operator () (A1 a1, A2 a2){
        return _f(a1, a2);
    }
private:
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
    R operator () (A1 a1, A2 a2, A3 a3){
        return _f(a1, a2, a3);
    }
private:
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
    R operator () (A1 a1, A2 a2, A3 a3, A4 a4){
        return _f(a1, a2, a3, a4);
    }
private:
    f_t _f;
};

} //namespace base
} //namespace jcx

#endif   /* JCX_BASE_CALLER_H */
