#ifndef  JCX_BASE_IRUNNABLE_H
#define  JCX_BASE_IRUNNABLE_H


#include <jcx/base/Macro.h>

namespace jcx { 
namespace base {

class IRunnable{
public:
    IRunnable(){}
    virtual ~IRunnable(){}
    virtual void run()  = 0;
private:
    JCX_NO_COPY_CTORS(IRunnable);
};

} //namespace base
} //namespace jcx

#endif   /* IRUNNABLE_H */
