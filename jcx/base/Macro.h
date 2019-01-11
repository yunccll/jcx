#ifndef  JCX_BASE_MACRO_H
#define  JCX_BASE_MACRO_H

//namespace jcx{
//namespace base{

#undef JCX_NO_COPY_CTORS
#define JCX_NO_COPY_CTORS(T) \
    T(const T &);            \
    void operator=(const T &)

#undef JCX_NO_DEFAULT_CTORS
#define JCX_NO_DEFAULT_CTORS(T) \
    T();                         \
    T(const T &);                \
    void operator=(const T &)

//} //namespace base
//} //namespace jcx

#ifdef __cplusplus
#define SGE_API extern "C"
#else
#define SGE_API extern
#endif

#endif   /* JCX_BASE_MACRO_H */
