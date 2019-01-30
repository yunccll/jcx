
#ifndef  JCX_PERF_CODEBLOCK_H
#define  JCX_PERF_CODEBLOCK_H

#include <string>

namespace jcx { 
namespace perf {

class IElapseRecorder;

class CodeBlock final {
public:
    CodeBlock(IElapseRecorder & elapseRecorder);
    CodeBlock(IElapseRecorder & elapseRecorder, const char * name);
    ~CodeBlock();

    const std::string & name(){
        return _name;
    }
private:
    IElapseRecorder & _elapseRecorder;
    std::string _name;
};

} //namespace perf
} //namespace jcx

#endif   /* JCX_PERF_CODEBLOCK_H */
