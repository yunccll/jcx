#ifndef  JCX_THREAD_MUTEX_H
#define  JCX_THREAD_MUTEX_H

#include <jcx/base/Crossplatform.h>

namespace jcx { 
namespace thread { 

class Mutex{
public:
    Mutex(){}
    virtual ~Mutex(){}

    virtual void lock() = 0;
    virtual int tryLock() = 0;
    virtual void unlock() = 0;
private:
    JCX_NO_COPY_CTORS(Mutex);
};

Mutex * newMutex();

class RwMutex{
public:
    RwMutex(){}
    virtual ~RwMutex(){}

    virtual void rlock() = 0;
    virtual void wlock() = 0;
    virtual void unlock() = 0;
private:
    JCX_NO_COPY_CTORS(RwMutex);
};

RwMutex * newRwMutex();

class ScopeTryLock{
public:
    ScopeTryLock(Mutex & m)
    :_m(m)
    {
        _ret = _m.tryLock();
    }
    ~ScopeTryLock(){
        if(_ret == 0){
            _m.unlock(); 
            _ret = 1;
        }
    }

    bool isLock() const { return _ret == 0; }
    int getRet() const  { return _ret; }
private:
    JCX_NO_DEFAULT_CTORS(ScopeTryLock);
    Mutex & _m;
    int _ret;
};

class ScopeLock{
public:
    ScopeLock(Mutex & m)
    :_m(m){
        _m.lock();
    }
    ~ScopeLock(){
        _m.unlock(); 
    }
private:
    JCX_NO_DEFAULT_CTORS(ScopeLock);
    Mutex & _m;
};

class ScopeRlock{
public:
    ScopeRlock(RwMutex & rwm)
    :_rwm(rwm){
        _rwm.rlock();
    }
    ~ScopeRlock(){
        _rwm.unlock();
    }
private:
    JCX_NO_DEFAULT_CTORS(ScopeRlock);
    RwMutex & _rwm;
};

class ScopeWlock{
public:
    ScopeWlock(RwMutex & rwm)
    :_rwm(rwm){
        _rwm.wlock();
    }
    ~ScopeWlock(){
        _rwm.unlock();
    }
private:
    JCX_NO_DEFAULT_CTORS(ScopeWlock);
    RwMutex & _rwm;
};

} // namespace thread
} // namespace jcx


#endif   /* JCX_THREAD_MUTEX_H */
