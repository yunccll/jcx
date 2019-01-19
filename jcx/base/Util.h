
#ifndef  JCX_BASE_UTIL_H
#define  JCX_BASE_UTIL_H

#include <jcx/base/Crossplatform.h>

namespace jcx { 
namespace base {

class Util{
public:
    template <typename T>  
    static std::shared_ptr<T> make_shared_array(size_t size)  
    {  
        return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());  
    }  
    template <typename T>  
    static std::unique_ptr<T> make_unique_array(size_t size)  
    {  
        std::unique_ptr<T> ret(new T[size], std::default_delete<T[]>());
        return ret;
    }


    static inline void printHex(const char * str, size_t len){
        for(size_t i = 0; i < len; ++i){
            printf("0x%X, ", str[i]);
        }
        std::cout << std::endl;
    }
    static inline void printHex(const std::string & str){
        printHex(&str.front(),str.size());
    }
private:
    JCX_NO_COPY_CTORS(Util); 
};

//TODO: Move to File 
bool readFileToString(const std::string & path, std::string & str);



//TODO: auto-free mem 's array & get length 
//class ScopeArray {
//}

} //namespace base
} //namespace jcx

#endif   /* BASEUTIL_H */
