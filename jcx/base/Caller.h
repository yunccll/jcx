
#ifndef  JCX_BASE_CALLER_H
#define  JCX_BASE_CALLER_H

namespace jcx {
namespace base {

template<typename R>
struct Caller0 final {
    typedef R (*f_t)(void);
    Caller0(f_t f)
    :_f(f)
    {
    }
    ~Caller0(){
    }

    R operator () (void){
        return _f();
    }
private:
    f_t _f;
};

template<typename R, typename A1>
struct Caller1 final {
    typedef R (*f_t)(A1);
    Caller1(f_t f)
    :_f(f)
    {
    }
    ~Caller1(){
    }
    R operator () (A1 a1){
        return _f(a1);
    }
private:
    f_t _f;
};

template<typename R, typename A1, typename A2>
struct Caller2 final {
    typedef R (*f_t)(A1, A2);
    Caller2(f_t f)
    :_f(f)
    {
    }
    ~Caller2(){
    }
    R operator () (A1 a1, A2 a2){
        return _f(a1, a2);
    }
private:
    f_t _f;
};

template<typename R, typename A1, typename A2, typename A3>
struct Caller3 final {
    typedef R (*f_t)(A1, A2, A3);
    Caller3(f_t f)
    :_f(f)
    {
    }
    ~Caller3(){
    }
    R operator () (A1 a1, A2 a2, A3 a3){
        return _f(a1, a2, a3);
    }
private:
    f_t _f;
};

template<typename R, typename A1, typename A2, typename A3, typename A4>
struct Caller4 final {
    typedef R (*f_t)(A1, A2, A3, A4);
    Caller4(f_t f)
    :_f(f)
    {
    }
    ~Caller4(){
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
