#include "Mutex.h"

#include <jcx/thread/PthreadMutex.h>

namespace jcx { 
namespace thread { 

Mutex * newMutex(){
    return new PthreadMutex();
}

RwMutex * newRwMutex(){
    return new PthreadRwMutex();
}

} // namespace thread
} // namespace jcx
