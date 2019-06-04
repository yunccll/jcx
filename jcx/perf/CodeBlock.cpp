#include "CodeBlock.h"

#include <jcx/perf/IElapseRecorder.h>

namespace jcx { 
namespace perf {

CodeBlock::CodeBlock(IElapseRecorder & elapseRecorder)
: CodeBlock(elapseRecorder, "")
{
}
CodeBlock::CodeBlock(IElapseRecorder & elapseRecorder, const char * name)
: _elapseRecorder(elapseRecorder)
, _name(name)
{
    _elapseRecorder.blockIn(_name);
}

CodeBlock::~CodeBlock(){
    _elapseRecorder.blockOut(_name);
}

} //namespace perf
} //namespace jcx
