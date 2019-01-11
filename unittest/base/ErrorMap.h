
#ifndef  JCX_SVR_ERRORMAP_H
#define  JCX_SVR_ERRORMAP_H

#include <jcx/base/DefaultErrorMap.h>

namespace jcx {
namespace svr {

using ::jcx::base::DefaultErrorMap;

class ErrorMap: public DefaultErrorMap{
public:
    enum ErrorCode {
        IdNotExist = 102,
    };

    ErrorMap(){
        errorItem(IdNotExist, "id not exist");
    }
    virtual ~ErrorMap(){
    }

};

}   //namespace svr
}   //namespace jcx

#endif   /* JCX_SVR_ERRORMAP_H */
