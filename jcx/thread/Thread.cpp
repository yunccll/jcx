#include <jcx/thread/Thread.h>
#include <jcx/logger/Logger.h>

//TODO detach , lock , cancel
using jcx::base::IRunnable;

namespace jcx { 
namespace thread { 

std::shared_ptr<Thread> Thread::make(IRunnable * r){
    return std::make_shared<Thread>(r);
}
std::shared_ptr<Thread> Thread::make(std::shared_ptr<IRunnable> spr){
    return std::make_shared<Thread>(spr.get());
}


Thread::Thread(IRunnable *  r)
:_runnable(r){
}

Thread::~Thread(){
}

void * Thread::ThreadEntry(void * ctx){
    Thread * thread = static_cast<Thread*>(ctx);
    if(thread == NULL){
        LOG_ERROR("thread ptr cast from ctx is NULL\n");
        return NULL;
    }
    thread->run();
    return NULL;
}

int Thread::detach(){
    int ret = ::pthread_detach(_thread);
    if(ret != 0)
        LOG_ERROR("thread join failed:[%d]\n", ret);
    return ret;
}
int Thread::start(){
    int ret = ::pthread_create(&_thread, NULL, ThreadEntry, this);
    if(ret != 0)
        LOG_ERROR("thread create failed:[%d]\n", ret);
    return ret;
}
int Thread::wait(){
    int ret = ::pthread_join(_thread, NULL);
    if(ret != 0)
        LOG_ERROR("thread join failed:[%d]\n", ret);
    return ret;
}

Thread::ThreadIdType Thread::id(){
    return (ThreadIdType)::pthread_self();
}

Thread::ThreadIdType Thread::self(){
    return Thread::id();
}
void Thread::sleep(unsigned int sec){
    //only for linux
    ::sleep(sec);
}
void Thread::msleep(unsigned int ms){
    //only for linux
    ::usleep(ms*1000);
}
void Thread::usleep(unsigned int micro){
    //only for linux
    ::usleep(micro);
}

void Thread::run(){
    if(_runnable){
        _runnable->run();
    }
}

} //namespace thread
} //namespace jcx
