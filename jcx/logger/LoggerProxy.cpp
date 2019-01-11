#include <jcx/logger/ILogger.h>
#include <jcx/logger/Factory.h>
#include <jcx/logger/ThreadLocal.h>
#include <jcx/logger/LoggerProxy.h>

namespace jcx {
namespace logger {

LoggerProxy::LoggerProxy()
: _loggerFactory(NULL)
,_pthreadLocalLogger(new ThreadLocal<ILogger>()){
}
LoggerProxy::~LoggerProxy(){
    if(_pthreadLocalLogger != NULL)
        delete _pthreadLocalLogger;
}

void LoggerProxy::setFactory(Factory * logFactory){
    ILogger * logger = _pthreadLocalLogger->get();
    if(logger != NULL){ 
        if(_loggerFactory != NULL)
            _loggerFactory->deleteLogger();
        else
            delete logger;
    }

    _pthreadLocalLogger->set(NULL); //for next calling to recreate ILogger
    _loggerFactory = logFactory;
}

ILogger * LoggerProxy::makeLogger(){
    if(_loggerFactory == NULL)
        _loggerFactory = new Factory();
    return _loggerFactory->createLogger();
}

ILogger* LoggerProxy::getLogger(){
    if(_pthreadLocalLogger->get() == NULL){
        _pthreadLocalLogger->set(this->makeLogger());
    }
    return _pthreadLocalLogger->get();
}

void LoggerProxy::info(const Info * info, const char * fmt, va_list ap){
    getLogger()->info(info, fmt, ap);
}
void LoggerProxy::debug(const Info * info, const char * fmt, va_list ap){
    getLogger()->debug(info, fmt, ap);
}
void LoggerProxy::warn(const Info * info, const char * fmt, va_list ap){
    getLogger()->warn(info, fmt, ap);
}
void LoggerProxy::error(const Info * info, const char * fmt, va_list ap){
    getLogger()->error(info, fmt, ap);
}


int LoggerProxy::setLevel(LogLevel::Level level){
    return getLogger()->setLevel(level);
}
LogLevel::Level LoggerProxy::getLevel(){
    return getLogger()->getLevel();
}
void LoggerProxy::flush(){
    getLogger()->flush();
}


#define vargs_to_valist(level_func, info, fmt) do { \
    va_list ap; \
    va_start(ap, fmt); \
    this->level_func(info, fmt, ap); \
    va_end(ap); \
} while(0)
void LoggerProxy::varInfo(const Info * info, const char * fmt, ...){
    vargs_to_valist(info, info, fmt);
}
void LoggerProxy::varDebug(const Info * info, const char * fmt, ...){
    vargs_to_valist(debug, info, fmt);
}
void LoggerProxy::varWarn(const Info * info, const char * fmt, ...){
    vargs_to_valist(warn, info, fmt);
}
void LoggerProxy::varError(const Info * info, const char * fmt, ...){
    vargs_to_valist(error, info, fmt);
}


} //namespace logger
} //namespace jcx
