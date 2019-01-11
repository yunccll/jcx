
#ifndef  JCX_LOGGER_LOGLEVEL_H
#define  JCX_LOGGER_LOGLEVEL_H

namespace jcx {
namespace logger {
class LogLevel {
public:
    enum Level {
        FATAL,
        ERROR,
        WARN,
        DEBUG,
        INFO,
        NOTE,
        MONI,
        MAX,
    };
private:
    LogLevel(const char ** levelNameTab, LogLevel::Level level);
public:
    static LogLevel * make(const char ** levelNameTab = 0, LogLevel::Level lvl = INFO);
    virtual ~LogLevel();


    inline const char* getName(Level lvl){
        //for performance -- no erro-check
        //if(_levelNameTable == 0)
            //this->initLevelName();
        //return (lvl >= 0 && lvl < MAX) ? _levelNameTable[lvl] : 0;
        return _levelNameTable[lvl];
    }
    inline bool canShow(Level showLevel){
        //for performance -- no erro-check
        //return showLevel >= 0 && _curLevel >= showLevel;
        return _curLevel >= showLevel;
    }
    inline int setCurrentLevel(Level level){
        if(level >= 0 && level < MAX && level != _curLevel){
            _curLevel = level;
            return true;
        }
        return false;
    }
    inline Level getCurrentLevel(){
        return _curLevel;
    }
private:
    void initLevelName();
    void resetLevelNameTab(const char ** levelNameTab);

    const char ** _levelNameTable;
    Level _curLevel;
};


} //namespace logger
} //namespace jcx

#endif   /* JCX_LOGGER_LOGLEVEL_H */
