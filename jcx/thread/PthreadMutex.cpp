#include "PthreadMutex.h"

namespace jcx { 
namespace thread { 

PthreadMutex::PthreadMutex(){
    ::pthread_mutex_init(&_mutex, NULL);
}
PthreadMutex::~PthreadMutex(){
    ::pthread_mutex_destroy(&_mutex);
}

void PthreadMutex::lock(){
    ::pthread_mutex_lock(&_mutex);
}

int PthreadMutex::tryLock(){
    return ::pthread_mutex_trylock(&_mutex);
}

void PthreadMutex::unlock(){
    ::pthread_mutex_unlock(&_mutex);
}

PthreadRwMutex::PthreadRwMutex(){
    ::pthread_rwlock_init(& _rwmutex, NULL);
}
PthreadRwMutex::~PthreadRwMutex(){
    ::pthread_rwlock_destroy(&_rwmutex);
}

void PthreadRwMutex::rlock(){
    ::pthread_rwlock_rdlock(&_rwmutex);
}
void PthreadRwMutex::wlock(){
    ::pthread_rwlock_wrlock(& _rwmutex);
}

void PthreadRwMutex::unlock(){
    ::pthread_rwlock_unlock(&_rwmutex);
}

} // namespace thread
} // namespace jcx
