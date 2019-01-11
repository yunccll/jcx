
#ifndef  JCX_BASE_DEFAULTERRORMAP_H
#define  JCX_BASE_DEFAULTERRORMAP_H

#include <jcx/base/IErrorMap.h>

namespace jcx {
namespace base {

class DefaultErrorMap : public IErrorMap{
public:
    enum ErrorCode {
        OK = 0,
        General,
        IOError,
    };

    DefaultErrorMap(){
        errorItem(OK, "OK");
        errorItem(General, "General error");
        errorItem(IOError, "IO error");
    }
    virtual ~DefaultErrorMap(){
    }
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_DEFAULTERRORMAP_H */
