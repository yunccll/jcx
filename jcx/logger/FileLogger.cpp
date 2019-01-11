#include <jcx/logger/FileLogger.h>
#include <jcx/logger/File.h>
#include <jcx/logger/Buffer.h> //TODO: why include this???

namespace jcx { 
namespace logger {


FileLogger::FileLogger(const char * path)
:_plogFile( new File(path)){
    _plogFile->open();
}
FileLogger::~FileLogger(){
    delete _plogFile;
}

void FileLogger::writeOut(){
    _plogFile->write(_logBuffer->buffer(), _logBuffer->realLen());
}
void FileLogger::flush(){
    _plogFile->flush();
}

} //namespace logger
} //namespace jcx
