#ifndef  JCX_LOGGER_DATETIME_H
#define  JCX_LOGGER_DATETIME_H

#include <jcx/base/Crossplatform.h>

namespace jcx { namespace logger {

class Int2StrTab;
class DateTime{
public:
    static std::shared_ptr<DateTime> now();
    DateTime();
    ~DateTime();

    int refresh();

    std::shared_ptr<char> getFormatString();
    int fill(char * buf, int len);

    static int fill(char * buf, int len, struct tm * datetime);

private:
    struct tm _now;



    struct datetime_tabs{
        Int2StrTab * _yearStrTab;
        Int2StrTab * _monthStrTab;
        Int2StrTab * _dayStrTab;
        Int2StrTab * _hourStrTab;
        Int2StrTab * _minuteStrTab;
        Int2StrTab * _secondStrTab;
        datetime_tabs();
        ~datetime_tabs();
        void initTabs();
        void freeTabs();
    };
    static datetime_tabs _tabs;
};




}} //namespace

#endif   /* DATETIME_H */
