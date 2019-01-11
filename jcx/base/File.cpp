#include <jcx/base/File.h>
#include <jcx/base/Crossplatform.h>
#include <jcx/base/Util.h>

namespace jcx { namespace base {

void File::deleteIt(const char * path){
    if(path){
        if( 0 != ::unlink(path)){
            if(errno ==  ENOENT) return ;
            printf("delete file error : %s", path);
        }
    }
    else
        printf("path is NULL!"); 
}
bool File::isExisting(const char * path){
    if(path){
        if( 0 == ::access(path, F_OK)){
            return true;
        }
        if(errno != ENOENT){
            printf("access file error : %s", path);
        }
    }
    else
        printf("path is NULL!"); 
    return false;
}

int File::create(const char * path){
    if(path){
        int fd = ::open(path, O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        if(fd >= 0){
            ::close(fd);
            return 0;
        }
        printf("create file error : %s", path);
        return -1;
    }
    printf("path is NULL!"); 
    return -1;
}

File::File(const char * path)
:_path(path){
}
File::~File(){
}
int File::read(char * buffer, int len){
    return 0;
}
int File::write(const char * buffer){
    return 0;
}
std::shared_ptr<char> File::getcwd(){
    auto ret = jcx::base::Util::make_shared_array<char>(MAXPATHLEN);
    if(NULL == ::getcwd(ret.get(), MAXPATHLEN)){
        printf("get current workding directory failed!");
        return  std::shared_ptr<char>();
    }
    return ret;
}

}} //namespace
