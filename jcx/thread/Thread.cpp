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
        return NULL;
    }
    thread->run();
    return NULL;
}

int Thread::detach(){
    return _imp->detach();
}
int Thread::start(){
    return _imp->entry(Thread::__ThreadEntry).create(this);
}
int Thread::wait(){
    return _imp->join();
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
