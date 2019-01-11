#include <jcx/logger/Buffer.h>
#include <jcx/base/Crossplatform.h>
#include <jcx/logger/Util.h>
#include <jcx/logger/DateTime.h>

namespace jcx {
namespace logger {

Buffer::int_to_str_tab Buffer::_tab;
Buffer::int_to_str_tab::int_to_str_tab():_intStrTab(0){
//    printf("[%s]:create the tab\n", __func__);
    _intStrTab = new Int2StrTab(999+1, 3);
}
Buffer::int_to_str_tab::~int_to_str_tab(){
    delete _intStrTab;
//    printf("[%s]:free the tab\n", __func__);
}

Buffer::Buffer(int bufCap){
    _cap = bufCap;
    _buffer = new char[_cap];
    _realLen = 0;
}
Buffer::~Buffer(){
    delete [] _buffer;
}

void Buffer::realloc(){
    delete _buffer;
    _buffer = new char[_cap <<= 1];
    if(_buffer == NULL){
        ERROR_TO_STDOUT("FATAL: no enough memory\n");
    }
    //ERROR_TO_STDOUT("realloc len %d\n", _cap);
}

void Buffer::write(const char * level, const Info * info, const char * fmt, va_list ap){
    _realLen = 0;
    //Maybe logHeader can be independented  in an single file
    int headerLen = logHeader(level, info);
    if(headerLen >= 0){
        int outLen = 0;
        char * output = logBody(fmt, ap, &outLen); //outLen include the '\0'
        if(output != NULL){
            if(_cap - headerLen >= outLen){
                memcpy(_buffer + headerLen, output, outLen);
                free(output);
                _realLen = headerLen + outLen - 1;
                return ;
            }
            else{
                char * ptr = new char[_cap];
                if(ptr == NULL){
                    printf("FATAL no enough memory\n");
                    _realLen = 0;
                    return ;
                }
                memcpy(ptr, _buffer, headerLen);
                do 
                    realloc();
                while(_cap - headerLen < outLen);

                memcpy(_buffer, ptr, headerLen);
                delete [] ptr;
                memcpy(_buffer + headerLen, output, outLen);
                free(output);
                _realLen = headerLen + outLen - 1;
            }
        }
    }
}

int Buffer::copyString(int offset, const char * str, const char suffix){
    int ret = strlen(str);
    strncpy(_buffer+offset, str, ret);
    _buffer[offset + ret] = suffix;
    return ret + 1;
}
int Buffer::copyInt(int offset, const int line, const char suffix){
    if(line < 1000){
        memcpy(_buffer+offset, (*_tab._intStrTab)[line], 3);
        _buffer[offset + 3] = suffix;
        return 4;
    }
    //lineno >= 1000
    char buf[16];
    int ret = snprintf(buf, sizeof(buf), "%d%c", line, suffix);
    strncpy(_buffer + offset, buf, ret);
    return ret;
}

int Buffer::fillDatetime(int offset, const char suffix){
//    static DateTime now;
//    now.refresh();
//    return now.fill(_buffer + offset, 21);

    struct tm tnow;
    time_t n = time(NULL); //big cpu consumer
    localtime_r(&n, &tnow); //big cpu consumer
    int ret = DateTime::fill(_buffer + offset, 21, &tnow);
    _buffer[offset + ret] = suffix;
    return ret + 1;
}

int Buffer::logHeader(const char * level, const Info * info){
    //1. fill -- level 
    int offset = 0;
    offset += copyString(offset, level, ' ');
    //2. fill the date
    offset += fillDatetime(offset, ' '); //Note: big cpu consumer
    //3. fill the file 
    offset += copyString(offset, info->file, ':');
    //4. fill the line
    offset += copyInt(offset, info->line, ' ');
    //5. fill the func 
//    offset += copyString(offset, info->func, ' ');
    return offset;
}
char * Buffer::logBody(const char * fmt, va_list ap, int * outLen){
    char * output = NULL;
    int ret = vasprintf(&output, fmt, ap); //Note : ret => len of string,  exclude the '\0' but the real output include the '\0'
    if(ret >= 0){ 
        *outLen = ret + 1;
        return output;
    }
    else{
        STRERROR_TO_STDOUT("log body error!");
        return NULL;
    }
}

} //namespace logger
} //namespace jcx
