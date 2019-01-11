#ifndef  JCX_LOGGER_ILOGGER_H
#define  JCX_LOGGER_ILOGGER_H

#include <cstdarg>
#include <jcx/logger/LogLevel.h>

namespace jcx { namespace logger {

struct Info{
    const char * file;
    int line;
    const char * func;
    const char * fmt;
};

class ILogger{
public:

    ILogger(){}
    virtual ~ILogger(){}

    virtual void info (const Info * info, const char * fmt, va_list ap) = 0;
    virtual void debug(const Info * info, const char * fmt, va_list ap)= 0;
    virtual void warn (const Info * info, const char * fmt, va_list ap) = 0;
    virtual void error(const Info * info, const char * fmt, va_list ap)= 0;

    virtual void flush() = 0;

    virtual int setLevel(LogLevel::Level level) = 0;
    virtual LogLevel::Level getLevel() = 0;
};

} } //namespace

#endif   /* ILOGGER_H */
