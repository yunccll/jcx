#ifndef  JCX_LOGGER_BUFFER_H
#define  JCX_LOGGER_BUFFER_H

#include <jcx/base/Crossplatform.h>
#include <jcx/logger/ILogger.h>

namespace jcx {  namespace logger {

class Int2StrTab;
class Buffer {
public:
    #define INIT_LOGGER_BUFFER      64*1024
    Buffer(int bufCap = INIT_LOGGER_BUFFER);
    ~Buffer();

    inline const char * buffer(){return _buffer;}
    inline const int cap(){return _cap;}
    inline const int realLen(){return _realLen;}

    void write(const char * level, const Info * info, const char * fmt, va_list ap);
    
private:
    void realloc();
    char * logBody(const char * fmt, va_list ap, int * outLen);

    int logHeader(const char * level, const Info * info);
    int fillDatetime(int offset, const char suffix);
    int copyInt(int offset, const int line, const char suffix);
    int copyString(int offset, const char * str, const char suffix);

private:
    int _cap;
    char * _buffer;
    int _realLen;


private:
    struct int_to_str_tab{
        Int2StrTab *_intStrTab;
        int_to_str_tab();
        ~int_to_str_tab();
    };
    static  int_to_str_tab _tab;
};

} } //namespace
#endif   /* LOGGERBUFFER_H */
