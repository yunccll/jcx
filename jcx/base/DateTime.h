
#ifndef  JCX_BASE_DATETIME_H
#define  JCX_BASE_DATETIME_H

#include <chrono>
#include <memory>

namespace jcx {
namespace base {


class DateTime final {
public:
    template<size_t unit>
    class IDurable final{
    public:
        IDurable(const unsigned long long num = 1):_unit(unit), _num(num){}
        virtual ~IDurable(){}

        unsigned long long seconds() const {return _num * _unit;}
        //std::shared_ptr<char> str(){return 0;} //TODO: ,and all sub class
        
    private:
        const int _unit;
        unsigned long long _num;
    };
    typedef IDurable<365*24*3600> Year;
    typedef IDurable<28*24*3600> Month28;
    typedef IDurable<29*24*3600> Month29;
    typedef IDurable<30*24*3600> Month30;
    typedef IDurable<31*24*3600> Month31;
    typedef IDurable<24*3600> Day;
    typedef IDurable<3600> Hour;
    typedef IDurable<60> Minute;
    typedef IDurable<1> Second;

public:
    DateTime();
    explicit DateTime(time_t dt);
    DateTime(const DateTime & dt);
    ~DateTime();

    static const DateTime now(){
        time_t t= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        return DateTime(t);
    }
    static std::shared_ptr<DateTime> make(){
        return std::shared_ptr<DateTime>(new DateTime(0));
    }

    static std::shared_ptr<DateTime> make(time_t dt){
        return std::shared_ptr<DateTime>(new DateTime(dt));
    }
    static std::shared_ptr<DateTime> make(const DateTime & dt){
        return std::shared_ptr<DateTime>(new DateTime(dt));
    }

    //string convert
    static std::shared_ptr<DateTime> from(const char * strDateTime, const char * fmt="%Y-%m-%d %H:%M:%S");
    const char * str(char * buffer, int cap) const;
    std::shared_ptr<char> str() const;

    DateTime & operator = (const DateTime & right) {
        _dt = right._dt;
        return *this;
    }

    // operators   == != , + , - , += , -=
    bool operator == (const DateTime & right) const{
        return this == &right || right._dt == _dt;
    }
    bool operator != (const DateTime & right) const{
        return !(*this).operator ==(right);
    }

    template<typename IDurable>
    const DateTime operator +(const IDurable & t) const{
        DateTime dt(*this);
        dt += t;
        return dt;
    }
    template<typename IDurable>
    const DateTime operator -(const IDurable & t) const{
        DateTime dt(*this);
        dt -= t;
        return dt;
    }
    const unsigned long long operator -(const DateTime & dt) const{
        return _dt - dt._dt;
    }

    template<typename IDurable>
    const DateTime& operator += (const IDurable & t){
        _dt += t.seconds();
        if(_dt <= 0) _dt = 0;
        return *this;
    }
    template<typename IDurable>
    const DateTime & operator -= (const IDurable & t){
        _dt -= t.seconds();
        if(_dt <=0) _dt = 0;
        return *this;
    }

private:
    time_t _dt;
};

template<typename IDurable>
const DateTime operator +(const IDurable & t, const DateTime & right){
    DateTime dt(right);
    dt += t;
    return dt;
}
template<typename IDurable>
const DateTime operator -(const IDurable & t, const DateTime & right){
    DateTime dt(right);
    dt -= t;
    return dt;
}

template<typename IDurable>
const DateTime& operator += (const IDurable & t, DateTime & left){
    left += t;
    return left;
}
template<typename IDurable>
const DateTime & operator -= (const IDurable & t, DateTime & left){
    left -= t;
    return left;
}

} //namespace base
} //namespace jcx

#endif   /* JCX_BASE_DATETIME_H */
