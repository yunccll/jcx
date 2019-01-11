#ifndef  JCX_LOGGER_UTIL_H
#define  JCX_LOGGER_UTIL_H

namespace jcx {
namespace logger {

class Util{
public:
    static void error_to_stdout_with_strerror(const char * file, const int line, const char* msg);
    static void error_to_stdout(const char * file, const int line, const char* msg);
};


class Int2StrTab{
public:
    Int2StrTab(int len, int width);
    ~Int2StrTab();

    char * operator[](int val){return _tab[val];}
    int getLength() const {return _len;}
    int getWidth() const {return _width;}
    int isValid(int val){ return val >= 0 && val < _len;}



private:
    char ** create_tab(int len, int width);
    void free_two_width_tab(char ** tab, int len);
private:
    char ** _tab;
    int _len;
    int _width;
};


} //namespace logger
} //namespace jcx

#define STRERROR_TO_STDOUT(msg)    jcx::logger::Util::error_to_stdout_with_strerror(__FILE__, __LINE__, msg)

#define STRERROR_TO_STDOUT_2ARG(msg, detail)    do{ \
    std::string errinfo(msg); \
    errinfo += detail; \
    jcx::logger::Util::error_to_stdout_with_strerror(__FILE__, __LINE__, errinfo.c_str()); \
}while(0)


#define ERROR_TO_STDOUT(msg)    jcx::logger::Util::error_to_stdout(__FILE__, __LINE__, msg)
#define ERROR_TO_STDOUT_2ARG(msg, detail)    do{ \
    std::string errinfo(msg); \
    errinfo += detail; \
    jcx::logger::Util::error_to_stdout(__FILE__, __LINE__, errinfo.c_str()); \
}while(0)

#endif   /* UTIL_H */
