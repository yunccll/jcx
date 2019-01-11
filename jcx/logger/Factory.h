#ifndef  JCX_LOGGER_FACTORY_H
#define  JCX_LOGGER_FACTORY_H

#include <jcx/base/Crossplatform.h>

namespace jcx { namespace logger {

class ILogger;

class Factory{
public:
    Factory();
    virtual ~Factory();

    virtual ILogger * create();

    ILogger * createLogger();
    void deleteLogger();

protected:
    ILogger * _logger;
};

class DefaultLoggerFactory : public Factory{
public:
    virtual ILogger * create();
};

class StdoutFactory : public Factory{
public:
    virtual ILogger * create();
};

class FileLoggerFactory : public Factory{
public:
    FileLoggerFactory(const char * fnPattern);
    virtual ~FileLoggerFactory();
    virtual ILogger * create();
private:
    int _seqNo;
    std::string _fnPattern;
};

}} //namespace

#endif   /* LOGFACTORY_H */
