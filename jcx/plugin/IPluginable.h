#ifndef  JCX_PLUGIN_IPLUGINABLE_H
#define  JCX_PLUGIN_IPLUGINABLE_H

namespace jcx { 
namespace plugin {

class IPluginable{
public:
    virtual ~IPluginable();

    template<typename T> 
    T * as(){
        return dynamic_cast<T*>(this);
    }
    static IPluginable Null;
};

} //namespace plugin
} //namespace jcx

#endif   /* JCX_PLUGIN_IPLUGINABLE_H */
