
#ifndef  JCX_LOGGER_FILE_H
#define  JCX_LOGGER_FILE_H

#include <string>
#include <cstdio>

namespace jcx { namespace logger {

class File{
public:
    static void deleteIt(const char * path);
    static int create(const char * path);
    static bool isExisting(const char * path);
    
public:
    File(const char * path);
    ~File();

    bool isOpen() {return _fp != NULL;}

    int open();
    int close();

    int reset();

    int write(const char * msg, const int len);

    int flush();

    const char * getPath(){return _path.c_str();}


private:
    std::string _path;
    FILE * _fp;
};

}} //namespace

#endif   /* LOGGERFILE_H */
