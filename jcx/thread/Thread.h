#ifndef  JCX_BASE_THREAD_H
#define  JCX_BASE_THREAD_H

#include <memory>
#include <pthread.h>
#include <jcx/base/IRunnable.h>

namespace jcx { 

namespace base {
    class IRunnable;
}

namespace thread { 


class Thread : public base::IRunnable{
private:
public:

    static std::shared_ptr<Thread> make(base::IRunnable * r);
    static std::shared_ptr<Thread> make(std::shared_ptr<base::IRunnable> spr);

    Thread(base::IRunnable * r = 0);
    ~Thread() override;
    void run() override;


    int detach();
    int start();
    int wait();

    typedef unsigned long ThreadIdType;
    ThreadIdType self();


    static ThreadIdType id();
    static ThreadIdType prettyId(){ return Thread::id() & 0xffff ;}
    static void sleep(unsigned int sec);
    static void msleep(unsigned int ms);
    static void usleep(unsigned int micro);

private:
    static void * ThreadEntry(void * ctx);
private:
    pthread_t _thread;  //TODO: move to Imp;
    base::IRunnable * _runnable;
};

} // namespace thread
} // namespace jcx

#endif   /* THREAD_H */
