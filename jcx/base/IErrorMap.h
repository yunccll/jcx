
#ifndef  JCX_BASE_IERRORMAP_H
#define  JCX_BASE_IERRORMAP_H

#include <jcx/base/Crossplatform.h>

namespace jcx {
namespace base {

struct error {
    int code ;
    const char * msg;
};

class IErrorMap{
public:

    IErrorMap(){
    }
    virtual ~IErrorMap(){}

    inline const char * getMsg(int code)const {
        return code >= 0 && code < (int)(_errors.size()) ? _errors[code].msg : "Unkown error code";
    }
    inline const int size() const {return (const int)_errors.size();}


protected:
    inline void assignWith(const IErrorMap& emap){
        _errors.assign(emap._errors.begin(), emap._errors.end());
    }
    inline void resize(int max){
        _errors.resize(max);
    }
    inline void errorItem(int code, const char * msg){
       if(code >= size()) resize(code+1);
       error err = {code, msg};
       _errors[code] = err;
    }

private:
    std::vector<error> _errors;
    JCX_NO_COPY_CTORS(IErrorMap);
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_IERRORMAP_H */
