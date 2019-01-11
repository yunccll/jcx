
#ifndef  JCX_BASE_SLICE_H
#define  JCX_BASE_SLICE_H

#include <jcx/base/Crossplatform.h>

namespace jcx {
namespace base {

class Slice{
public:
    Slice():_str(NULL), _size(0){}
    Slice(const char * str) : _str(str), _size(str != NULL ? strlen(str) : 0) {}
    Slice(const char * str, int size) : _str(str), _size(size) {}
    Slice(const Slice & sl) : _str(sl._str), _size(sl._size) {}
    ~Slice(){}

    //TODO: equal ???? 
    bool empty() const {return _size == 0;}

    const char * str() const {return _str;}
    uint32_t size() const {return _size;}

    std::string toString() const {return std::string(_str, _size);}

private:
    const char * _str;
    uint32_t _size;
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_SLICE_H */
