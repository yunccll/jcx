#ifndef  JCX_THREAD_PTHREADMUTEX_H
#define  JCX_THREAD_PTHREADMUTEX_H

#include <jcx/base/Macro.h>
#include <jcx/thread/Mutex.h>
#include <pthread.h>

namespace jcx { 
namespace thread { 

class PthreadMutex : public Mutex{
public:
    PthreadMutex();
    virtual ~PthreadMutex();

    virtual void lock();
    virtual int tryLock();
    virtual void unlock();
private:
    JCX_NO_COPY_CTORS(PthreadMutex);
    pthread_mutex_t _mutex;
};

class PthreadRwMutex : public RwMutex {
public:
    PthreadRwMutex();
    virtual ~PthreadRwMutex();

    virtual void rlock();
    virtual void wlock();

    virtual void unlock();
private:
    JCX_NO_COPY_CTORS(PthreadRwMutex);
    pthread_rwlock_t _rwmutex;
};

} // namespace thread
} // namespace jcx

#endif   /* JCX_THREAD_PTHREADMUTEX_H */
