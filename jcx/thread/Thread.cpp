#include <jcx/thread/Thread.h>
#include <jcx/logger/Logger.h>
#include <jcx/thread/IThreadImp.h>
//TODO: cancel
using jcx::base::IRunnable;

namespace jcx { 
namespace thread { 

std::shared_ptr<Thread> Thread::make(IRunnable * r){
    return std::make_shared<Thread>(r);
}
std::shared_ptr<Thread> Thread::make(std::shared_ptr<IRunnable> spr){
    return std::make_shared<Thread>(spr.get());
}

Thread::Thread()
:_imp(IThreadImp::newInstance())
,_runnable(0){
}

Thread::Thread(IRunnable *  r)
:_imp(IThreadImp::newInstance())
,_runnable(r){
}

Thread::~Thread(){
}

void * Thread::__ThreadEntry(void * ctx){
    Thread * thread = static_cast<Thread*>(ctx);
    if(thread == NULL){
        LOG_ERROR("thread ptr cast from ctx is NULL\n");
        return NULL;
    }
    thread->run();
    return NULL;
}

int Thread::detach(){
    int ret = _imp->detach();
    if(ret != 0)
        LOG_ERROR("thread join failed:[%d]\n", ret);
    return ret;
}
int Thread::start(){
    int ret = _imp->entry(Thread::__ThreadEntry).create(this);
    if(ret != 0)
        LOG_ERROR("thread create failed:[%d]\n", ret);
    return ret;
}
int Thread::wait(){
    int ret = _imp->join();
    if(ret != 0)
        LOG_ERROR("thread join failed:[%d]\n", ret);
    return ret;
}

Thread::ThreadIdType Thread::id(){
    return IThreadImp::id();
}

Thread::ThreadIdType Thread::self(){
    return Thread::id();
}
void Thread::sleep(unsigned int sec){
    //only for linux
    IThreadImp::sleep(sec);
}
void Thread::msleep(unsigned int ms){
    //only for linux
    IThreadImp::usleep(ms*1000);
}
void Thread::usleep(unsigned int micro){
    //only for linux
    IThreadImp::usleep(micro);
}

void Thread::run(){
    if(_runnable){
        _runnable->run();
    }
}

} //namespace thread
} //namespace jcx
