#ifndef  JCX_LOGGER_LOGGERBASE_H
#define  JCX_LOGGER_LOGGERBASE_H

#include <cstdarg>
#include <jcx/logger/ILogger.h>

namespace jcx{
namespace logger{

class Buffer;
class LogLevel;

class LoggerBase : public ILogger{
public:
    LoggerBase();
    virtual ~LoggerBase();
    
    virtual void writeOut() = 0;
    virtual void flush() = 0;

    //TODO: will reduce the interface into other files
    virtual void info (const Info * info, const char * fmt, va_list ap);
    virtual void debug(const Info * info, const char * fmt, va_list ap);
    virtual void warn (const Info * info, const char * fmt, va_list ap);
    virtual void error(const Info * info, const char * fmt, va_list ap);


    virtual int setLevel(LogLevel::Level level);
    virtual LogLevel::Level getLevel();

protected:
    void writeLog(LogLevel::Level level, const Info * info, const char * fmt, va_list ap);

    Buffer * _logBuffer;
    LogLevel * _logLevel;
};


} //namespace logger
} //namespace jcx

#endif   /* JCX_LOGGER_LOGGERBASE_H */
