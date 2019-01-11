#include <jcx/logger/LoggerBase.h>
#include <jcx/base/Crossplatform.h>
#include <jcx/logger/Buffer.h>
#include <jcx/logger/LogLevel.h>

namespace jcx {
namespace logger {

LoggerBase::LoggerBase()
:_logBuffer(new Buffer())
,_logLevel(LogLevel::make()){
}
LoggerBase::~LoggerBase(){
    delete _logLevel;
    delete _logBuffer;
}
    
void LoggerBase::writeLog(LogLevel::Level level, const Info * info, const char * fmt, va_list ap){
    if(_logLevel->canShow(level)){
        _logBuffer->write(_logLevel->getName(level), info, fmt, ap);
        writeOut();
    }
}
void LoggerBase::info(const Info * info, const char * fmt, va_list ap){
    this->writeLog(LogLevel::INFO, info, fmt, ap);
}

void LoggerBase::debug(const Info * info, const char * fmt, va_list ap){
    this->writeLog(LogLevel::DEBUG, info, fmt, ap);
}
void LoggerBase::warn(const Info * info, const char * fmt, va_list ap){
    this->writeLog(LogLevel::WARN, info, fmt, ap);
}
void LoggerBase::error(const Info * info, const char * fmt, va_list ap){
    this->writeLog(LogLevel::ERROR, info, fmt, ap);
}

int LoggerBase::setLevel(LogLevel::Level level){
    return _logLevel->setCurrentLevel(level);
}
LogLevel::Level LoggerBase::getLevel(){
    return _logLevel->getCurrentLevel();
}

} //namespace logger
} //namespace jcx


