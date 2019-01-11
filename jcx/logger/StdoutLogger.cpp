#include <jcx/logger/StdoutLogger.h>
#include <jcx/base/Crossplatform.h>
#include <jcx/logger/Buffer.h> //TODO: Why include this

namespace jcx {
namespace logger {

StdoutLogger::StdoutLogger(){
}
StdoutLogger::~StdoutLogger(){
}
void StdoutLogger::writeOut(){
    printf("%s", _logBuffer->buffer());
}
void StdoutLogger::flush(){
}

} //namespace logger
} //namespace jcx
