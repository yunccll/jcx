#ifndef  JCX_BASE_ERROR_H
#define  JCX_BASE_ERROR_H

#include <jcx/base/Crossplatform.h>
#include <jcx/base/Slice.h>
#include <jcx/base/DefaultErrorMap.h>

namespace jcx {
namespace base {

template<typename ErrorMap = DefaultErrorMap>
class Error {
public:
    inline static char * copyContext(const char * str, uint32_t size){
        if(str != NULL && size != 0){
            char * dest = new char[size+1];
            memcpy(dest, str, size);
            dest[size] = 0;
            return dest;
        }
        return NULL; 
    }
    Error() : _code(0), _msg(""), _ctx(NULL) {}
    Error(int code) : _code(code), _msg(_errorMap.getMsg(code)), _ctx(NULL){}
    Error(int code, const Slice & ctx): _code(code),_msg(_errorMap.getMsg(code)){
       _ctx = copyContext(ctx.str(), ctx.size());
    }
    Error(const Error & err){
        _code = err._code;
        _msg = err._msg;
        _ctx = copyContext(err._ctx, (err._ctx == NULL) ? 0 : strlen(err._ctx));
    }
    ~Error(){
        if(_ctx == NULL) delete _ctx;
    }

    static Error OK(){
        return Error(DefaultErrorMap::OK);
    }
    static Error Failed(){
       return Error(DefaultErrorMap::General);
    }
    static Error IOError(const char * ctx = ""){
        char buf[512];
        snprintf(buf, sizeof(buf), "%s:%s", ctx, strerror(errno));
        return Error(DefaultErrorMap::IOError, buf);
    }
    static Error IOError(const std::string & ctx){
        return IOError(ctx.c_str());
    }

    const int code() const {return -1 *_code;}
    const char * msg() const { return _msg; }
    const char * ctx() const { return _ctx;}

    std::string toString() const {
        std::string ret = std::to_string(code());
        ret += " : "; 
        ret += msg() ? msg() : "";
        ret += " : "; 
        ret += ctx() ? ctx() : "";
        return ret;
    }
    bool ok(){
        return _code == 0;
    }

private:
    int _code;
    const char *  _msg;
    char * _ctx;
    static ErrorMap _errorMap;
};

template<typename ErrorMap> 
ErrorMap Error<ErrorMap>::_errorMap;

template<typename T = ::jcx::base::DefaultErrorMap>
using Status = ::jcx::base::Error<T>;


}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_ERROR_H */
