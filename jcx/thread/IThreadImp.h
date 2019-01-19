
#ifndef  JCX_THREAD_ITHREADIMP_H
#define  JCX_THREAD_ITHREADIMP_H

#include <jcx/base/Macro.h>

namespace jcx { 
namespace thread { 

typedef void * (*ThreadEntry)(void * ctx);

class IThreadImp {
public:
    IThreadImp() {}
    virtual ~IThreadImp() {}

    virtual IThreadImp & entry(ThreadEntry entry) = 0;
    virtual ThreadEntry entry() const = 0;

    //virtual int id() = 0; //TODO: 

    virtual int create(void * ctx) = 0;
    virtual int join() = 0;
    virtual int detach() = 0;


    static IThreadImp * newInstance();
    static int id();
    static unsigned int sleep(unsigned int sec);
    static int usleep(unsigned long long sec);
    
private:
    JCX_NO_COPY_CTORS(IThreadImp); 
};


} // namespace thread
} // namespace jcx

#endif   /* JCX_THREAD_ITHREADIMP_H */
