#ifndef  JCX_LOGGER_LOGGER_H
#define  JCX_LOGGER_LOGGER_H

#include <jcx/logger/LoggerBase.h>

namespace jcx { 
namespace logger {

class StdoutLogger : public LoggerBase{
public:
    StdoutLogger();
    virtual ~StdoutLogger();
    virtual void writeOut();
    virtual void flush();
};

}} //namespace

#endif   /* LOGGERS_H */
