#ifndef  JCX_BASE_FILE_H
#define  JCX_BASE_FILE_H

#include <string>
#include <memory>

#include <jcx/base/Macro.h>

namespace jcx { 
namespace base {

//TODO: Split into FileInfo && File
class File{
public:
    static std::shared_ptr<char> getcwd();
    static void deleteIt(const char * path);
    static int create(const char * path);
    static bool isExisting(const char * path);
    static bool isModify(const char * path); //TODO: 

public:
    File(const char * path);
    ~File();

    int read(char * buffer, int len); //TODO:
    int write(const char * buffer); //TODO:
    int flush(); //TODO:

    const char * getPath(){ return _path.c_str();}

private: 
    JCX_NO_COPY_CTORS(File);
    std::string _path;

};

}  //namespace base
} // namespace jcx

#endif   /* FILE_H */
