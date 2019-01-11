#include <jcx/logger/LogLevel.h>

namespace jcx {
namespace logger {

LogLevel::LogLevel(const char ** levelNameTab, LogLevel::Level level)
:_levelNameTable(levelNameTab)
, _curLevel(level){
}
LogLevel::~LogLevel(){
}
LogLevel * LogLevel::make(const char ** levelNameTab, LogLevel::Level level){
    LogLevel * ret = new LogLevel(levelNameTab, level);
    if(levelNameTab == 0){
        ret->initLevelName();
    }
    else{
        ret->resetLevelNameTab(levelNameTab); 
    }
    return ret;
}

void LogLevel::initLevelName(){
    static const char * levelNameTab [] ={
        "FATAL",
        "ERROR",
        "WARN ",
        "DEBUG",
        "INFO ",
        "NOTE ",
        "MONI ",        
    };
    _levelNameTable = levelNameTab;
}
void LogLevel::resetLevelNameTab(const char ** levelNameTab){
    if(levelNameTab != _levelNameTable){
        _levelNameTable = levelNameTab;
    }
}

} //namespace logger
} //namespace jcx
