#ifndef  JCX_LOGGER_THREADLOCAL_H
#define  JCX_LOGGER_THREADLOCAL_H

#include <pthread.h>
#include <memory>

#include <jcx/base/Builder.h>
#include <jcx/logger/Util.h>

namespace jcx { 
namespace logger {

template <typename T>
class ThreadLocal{
private:
    ThreadLocal & operator = (const ThreadLocal & r);
    ThreadLocal(const ThreadLocal & r);
public:
    static std::shared_ptr<ThreadLocal<T>> make(){
        return jcx::base::BuilderSptr<ThreadLocal<T>>::make();
    }

    ThreadLocal(){
        if(0 != pthread_key_create(&_key, NULL))
            STRERROR_TO_STDOUT("pthread_key_create failed.");
    }
    ~ThreadLocal(){
        if(0 != pthread_key_delete(_key))
            STRERROR_TO_STDOUT("pthread_key_delete failed.");
    }

    void set(const T * ptr){
        if(0 != pthread_setspecific(_key, (void*)ptr))
            STRERROR_TO_STDOUT("pthread_setspecific failed.");
    }
    T * get() const {
        return static_cast<T * >(pthread_getspecific(_key));
    }
private:
    pthread_key_t _key;
};

} //namespace logger
} //namespace jcx

#endif   /* THREADLOCAL_H */
