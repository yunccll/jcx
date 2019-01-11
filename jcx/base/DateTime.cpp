#include "DateTime.h"

#include <jcx/base/Crossplatform.h>
#include <jcx/base/Util.h>

namespace jcx {
namespace base {


std::shared_ptr<DateTime> DateTime::now(){
    time_t t= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return std::shared_ptr<DateTime>(new DateTime(t));
}
std::shared_ptr<DateTime> DateTime::make(){
    return std::shared_ptr<DateTime>(new DateTime);
}
std::shared_ptr<DateTime> DateTime::make(time_t dt){
    return std::shared_ptr<DateTime>(new DateTime(dt));
}
std::shared_ptr<DateTime> DateTime::make(const DateTime & dt){
    return std::shared_ptr<DateTime>(new DateTime(dt));
}
std::shared_ptr<DateTime> DateTime::from(const char * strDateTime, const char * fmt){
    if(strDateTime != 0 && fmt != 0){
        struct tm time_tmp = {0};
        if(0 != strptime(strDateTime, fmt, &time_tmp)){
            time_t cur_t = mktime(&time_tmp);
            if(cur_t != -1){
                return DateTime::make(cur_t);
            }
        }
    }
    return std::shared_ptr<DateTime>();
}

DateTime::DateTime(){
    _dt = 0;
}
DateTime::DateTime(time_t dt):_dt(dt){
}
DateTime::~DateTime(){
}

const char * DateTime::str(char * buffer, int cap) const{
    struct tm tm;
    localtime_r(&_dt, &tm);
    if(cap >= 20){
        snprintf(buffer,cap, "%04d-%02d-%02d %02d:%02d:%02d",
            (int)tm.tm_year + 1900,(int)tm.tm_mon + 1,(int)tm.tm_mday,
            (int)tm.tm_hour,(int)tm.tm_min,(int)tm.tm_sec);
            return buffer;
    }
    return 0;
}
std::shared_ptr<char> DateTime::str() const{
    std::shared_ptr<char> ret = Util::make_shared_array<char>(32);
    str(ret.get(), 32);
    return ret;
}


} //namespace base
} //namespace jcx
