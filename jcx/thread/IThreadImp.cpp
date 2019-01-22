#include "IThreadImp.h"
#include <jcx/base/Crossplatform.h>
#include <pthread.h>

//TODO: Crossplatform ??????
namespace jcx { 
namespace thread { 

class PthreadImp : public IThreadImp {
public:
    PthreadImp()
    :_entry(0){
    }
    explicit PthreadImp(ThreadEntry entry)
    :_entry(entry)
    {
    }

    ~PthreadImp() override {
    }

    IThreadImp & entry(ThreadEntry entry) override {
        if(entry != _entry)
            _entry = entry;
        return *this;
    }
    ThreadEntry entry() const override {
        return _entry;
    }

    int create(void * ctx) override {
        if(_entry == NULL) return -1;
        return ::pthread_create(&_pthread, NULL, _entry, ctx);
    }
    int join() override {
        return ::pthread_join(_pthread, NULL);
    }
    int detach() override{
        return ::pthread_detach(_pthread);
    }

    static unsigned long id(){
        return (unsigned long)(::pthread_self());
    }

private:
    JCX_NO_COPY_CTORS(PthreadImp);
    ThreadEntry _entry;
    pthread_t _pthread;

};

IThreadImp * IThreadImp::newInstance(){
    return new PthreadImp();
}

int IThreadImp::id(){
    return PthreadImp::id();
}
unsigned int IThreadImp::sleep(unsigned int sec){
    return ::sleep(sec);
}
int IThreadImp::usleep(unsigned long long us){
    return ::usleep(us);
}


} //namespace thread
} //namespace jcx
