
#ifndef  JCX_BASE_EVENT_H
#define  JCX_BASE_EVENT_H

#include <string>
#include <jcx/base/Macro.h>

namespace jcx {
namespace base {


class Event  {
public:
    Event(const int id, void * arg);
    virtual ~Event();

    virtual std::string toString() const;

    int getId() const { return _id; }
    void setId(const int id) { _id = id; }

    void * getArg() const { return _arg; }
    void setArg(void * arg) { _arg = arg; }

private:
    JCX_NO_COPY_CTORS(Event);
    uint32_t  _id;
    void * _arg;
};

}   //namespace base
}   //namespace jcx

#endif   /* EVENT_H */
