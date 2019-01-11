#include <jcx/logger/DateTime.h>
#include <jcx/logger/Util.h>

namespace jcx { 
namespace logger {

DateTime::datetime_tabs DateTime::_tabs;


DateTime::datetime_tabs::datetime_tabs(){
    _yearStrTab =  _monthStrTab = _dayStrTab = 0;
    _hourStrTab = _minuteStrTab = _secondStrTab = 0;
//    printf("[%s]:create the tabls\n", __func__);
    initTabs();
}
DateTime::datetime_tabs::~datetime_tabs(){
    freeTabs();
//    printf("[%s]:free the tabs\n", __func__);
}

void DateTime::datetime_tabs::initTabs(){
    if(!_yearStrTab) _yearStrTab = new Int2StrTab(9999+1, 4);
    Int2StrTab * two_60tab  = new Int2StrTab(59+1, 2);
    if(!_monthStrTab) _monthStrTab = two_60tab;
    if(!_dayStrTab) _dayStrTab = two_60tab;
    if(!_hourStrTab) _hourStrTab = two_60tab;
    if(!_minuteStrTab) _minuteStrTab = two_60tab;
    if(!_secondStrTab) _secondStrTab = two_60tab;
}
void DateTime::datetime_tabs::freeTabs(){
    if(_secondStrTab){
        delete _secondStrTab;
        _secondStrTab = 0;
    }
    if(_minuteStrTab) _minuteStrTab = 0;
    if(_hourStrTab) _hourStrTab = 0;
    if(_dayStrTab) _dayStrTab = 0;
    if(_monthStrTab) _monthStrTab = 0;
    if(_yearStrTab) {
        delete _yearStrTab;
        _yearStrTab = 0;
    }
}

std::shared_ptr<DateTime> DateTime::now(){
    return std::shared_ptr<DateTime>(new DateTime);
}
DateTime::DateTime(){
    refresh();
}
DateTime::~DateTime(){
}
int DateTime::fill(char * buf, int len){
    return DateTime::fill(buf, len, &_now);
}
int DateTime::refresh(){
    time_t n = time(NULL);
    if(NULL != localtime_r(&n, &_now)){
        return 0;
    }
    STRERROR_TO_STDOUT("call time() or localtime_r failed!");
    return -1;
}
std::shared_ptr<char> DateTime::getFormatString(){
    const int max_date_time_str_len = 32;
    auto ret = std::shared_ptr<char>(new char[max_date_time_str_len]);
    fill(ret.get(), max_date_time_str_len);
    return ret;
}


int DateTime::fill(char * buf, int len, struct tm * dt){
    if(len >= 20){
        memcpy(buf, (*_tabs._yearStrTab)[dt->tm_year+1900], 4);
        buf[4]  = '-';
        memcpy(buf+5, (*_tabs._monthStrTab)[dt->tm_mon+1], 2);
        buf[7] = '-';
        memcpy(buf+8, (*_tabs._dayStrTab)[dt->tm_mday], 2);
        buf[10] = ' ';
        memcpy(buf+11, (*_tabs._hourStrTab)[dt->tm_hour], 2);
        buf[13] = ':';
        memcpy(buf+14, (*_tabs._minuteStrTab)[dt->tm_min], 2);
        buf[16] = ':';
        memcpy(buf+17, (*_tabs._secondStrTab)[dt->tm_sec], 2);
        buf[19] = 0;
        return 19;
    }
    else return -1;
}
} //namespace logger
} //namespace jcx
