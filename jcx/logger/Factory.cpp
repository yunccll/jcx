#include <jcx/logger/Factory.h>
#include <jcx/logger/ILogger.h>
#include <jcx/logger/StdoutLogger.h>
#include <jcx/logger/FileLogger.h>

namespace jcx { 
namespace logger {

Factory::Factory()
:_logger(0){
}
Factory::~Factory(){
    deleteLogger();
}

ILogger * Factory::createLogger(){
    _logger = this->create();
    return _logger;
}

void Factory::deleteLogger(){
    if(_logger){
        delete _logger;
         _logger = 0;
    }
}

ILogger * Factory::create(){
    return new StdoutLogger();
}


ILogger * DefaultLoggerFactory::create(){
    return new StdoutLogger();
}


ILogger * StdoutFactory::create(){
    return new StdoutLogger();
}

FileLoggerFactory::FileLoggerFactory(const char * fnPattern)
:_seqNo(0){
    _fnPattern.assign(fnPattern);
}
FileLoggerFactory::~FileLoggerFactory(){
}
ILogger * FileLoggerFactory::create(){
    char fn[128] ;
    snprintf(fn, sizeof(fn), "%s.%03d.log", _fnPattern.c_str(), _seqNo++);
    return new FileLogger(fn);
}

} // namespace logger
} // namespace jcx
