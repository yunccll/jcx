
#ifndef  EVENT_H
#define  EVENT_H

#include <string>

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
    uint32_t  _id;
    void * _arg;
};

}   //namespace base
}   //namespace jcx

#endif   /* EVENT_H */
