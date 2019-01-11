#include "Util.h"

namespace jcx { 
namespace base {

bool readFileToString(const std::string & path, std::string & str){
    std::ifstream ifs(path.c_str(), std::ios::in|std::ios::binary); 
    if(ifs){
        const std::streamsize bufferLen = 1024*4;
        auto buffer = Util::make_shared_array<char>(bufferLen);
        do{
            ifs.read(buffer.get(), bufferLen);
            str.append(buffer.get(), ifs.gcount());
        }while(ifs.gcount() == bufferLen);
        return true;
    }
    return false;
}


} //namespace base
} //namespace jcx
