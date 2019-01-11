#include <jcx/logger/File.h>
#include <jcx/logger/Util.h>
#include <jcx/base/Crossplatform.h>

namespace jcx { 
namespace logger {

void File::deleteIt(const char * path){
    if(path){
        if( 0 != ::unlink(path)){
            if(errno ==  ENOENT) return ;
            STRERROR_TO_STDOUT_2ARG("delete file error :", path);
        }
    }
    else
        ERROR_TO_STDOUT("path is NULL!"); 
}
bool File::isExisting(const char * path){
    if(path){
        if( 0 == ::access(path, F_OK)){
            return true;
        }
        if(errno != ENOENT){
            STRERROR_TO_STDOUT_2ARG("access file error :", path);
        }
    }
    else
        ERROR_TO_STDOUT("path is NULL!"); 
    return false;
}

int File::create(const char * path){
    if(path){
        int fd = ::open(path, O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        if(fd >= 0){
            ::close(fd);
            return 0;
        }
        STRERROR_TO_STDOUT_2ARG("create file error :", path);
        return -1;
    }
    ERROR_TO_STDOUT("path is NULL!"); 
    return -1;
}
File::File(const char * path)
:_path(path), _fp(NULL){
}
File::~File(){
    if(_fp != NULL)
        close();
}
int File::open(){
    if(_fp == NULL){
        _fp = fopen(_path.c_str(), "a");
        if(_fp != NULL){
            return 0;
        }
        STRERROR_TO_STDOUT_2ARG("fopen file error : ", _path.c_str());
        return -1;
    }
    //_fp != NULL ==> error print , and return 0;
    ERROR_TO_STDOUT_2ARG("already opened : ", _path.c_str());
    return 0;
}

int File::close(){
    if(_fp != NULL){
        if(fclose(_fp) == 0){
            _fp = NULL;
            return 0;
        }
        STRERROR_TO_STDOUT_2ARG("fclose file Error : ", _path.c_str());
        _fp = NULL;
        return -1;
    }
    ERROR_TO_STDOUT_2ARG("maybe file is not opened : ", _path.c_str());
    return 0;
}

int File::reset(){
    if(_fp != NULL)
        if(close() == -1) return -1;
    return open();
}
int File::write(const char * msg, const int len){
    if(_fp != NULL){
        int ret = fwrite(msg, 1, len, _fp);
        if(ret == len) return ret;
        STRERROR_TO_STDOUT_2ARG("fwrite failed, ret< len : ", _path.c_str());
        return ret;
    }
    ERROR_TO_STDOUT_2ARG("open the file first : ", _path.c_str());
    return  -1;
}
int File::flush(){
    if(_fp != NULL){
        int ret = fflush(_fp);
        if(ret == 0) return 0;
        STRERROR_TO_STDOUT_2ARG("flush file error : ", _path.c_str());
        return  -1;
    }
    ERROR_TO_STDOUT_2ARG("open the file first : ", _path.c_str());
    return  -1;
}

} // namespace logger
} // namespace jcx
