#ifndef  JCX_LOGGER_FILELOGGER_H
#define  JCX_LOGGER_FILELOGGER_H

#include <jcx/logger/LoggerBase.h>

namespace jcx { namespace logger {

class File;

class FileLogger : public LoggerBase{
public:
    FileLogger(const char * path);
    virtual ~FileLogger();

    virtual void writeOut();
    virtual void flush();
private:
    File * _plogFile;
};

}} //namespace

#endif   /* FILELOGGER_H */
