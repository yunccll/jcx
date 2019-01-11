#include <iostream>
#include <jcx/base/TestCaseHelper.h>

using namespace std;

namespace jcx { 
namespace base {

int _Base::Gid = 0;
_Base::_Base()
:_id(_Base::Gid++){
    std::cout << "constructor of _Base, id:" << _id << std::endl;
}
_Base::~_Base(){
    std::cout << "destructor of _Base, id:" << _id << std::endl;
}
bool _Base::operator == (const _Base & right) const{
    cout << "_Base:" << __func__ << endl;
    return right._id == _id;
}

_Sub::_Sub(int id):_id(id){
    std::cout<< "_Sub constructor: " << _id << std::endl;
}
_Sub::~_Sub(){
    std::cout << "_Sub destructor: "<< _id << std::endl;
}
void _Sub::f(){
    std::cout << "override the _If 's functions" << _id << std::endl;
}

} //namespace base
} //namespace jcx
