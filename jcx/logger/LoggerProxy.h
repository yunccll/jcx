#ifndef  JCX_LOGGER_LOGGERPROXY_H
#define  JCX_LOGGER_LOGGERPROXY_H

#include <jcx/base/Singleton.h>
#include <jcx/logger/ILogger.h>

namespace jcx { namespace logger {

template <typename T> class ThreadLocal;
class Factory;

class LoggerProxy : public ILogger , public jcx::base::Singleton<LoggerProxy>{
private:
    LoggerProxy();
public:

    virtual ~LoggerProxy();
    
    virtual void info (const Info * info, const char * fmt, va_list ap);
    virtual void debug(const Info * info, const char * fmt, va_list ap);
    virtual void warn (const Info * info, const char * fmt, va_list ap);
    virtual void error(const Info * info, const char * fmt, va_list ap);

    virtual int setLevel(LogLevel::Level level);
    virtual LogLevel::Level getLevel();

    virtual void flush();

    void setFactory(Factory * loggerFactory);

    void varInfo (const Info * info, const char * fmt, ...);
    void varDebug(const Info * info, const char * fmt, ...);
    void varWarn (const Info * info, const char * fmt, ...);
    void varError(const Info * info, const char * fmt, ...);

private:
    ILogger * makeLogger();
    inline ILogger* getLogger();
private:
    Factory * _loggerFactory;
    ThreadLocal<ILogger>* _pthreadLocalLogger;

    SINGLETON(LoggerProxy);
};

}} //namespace

#endif   /* JCX_LOGGER_LOGGERPROXY_H */
