
#ifndef  JCX_PLUGIN_PLUGINCONTAINER_H
#define  JCX_PLUGIN_PLUGINCONTAINER_H


#include <jcx/base/HashMap.h>
#include <jcx/plugin/IPluginable.h>
#include <jcx/base/Iterator.h>

namespace jcx { 
namespace plugin {

class PluginContainer final {
public:
    PluginContainer();
    ~PluginContainer();

    IPluginable * find(const char * name);

    int add(const char * name, IPluginable * plugin);
    void remove(const char * name);

    auto iterator(){
        //return jcx::base::Iterator<typename jcx::base::HashMapForPtr<IPluginable>>(_plugins);
        return jcx::base::Iterator<typename jcx::base::HashMapForPtr<IPluginable>>(_plugins);
    }

private:
    jcx::base::HashMapForPtr<IPluginable> _plugins;
};

} //namespace plugin
} //namespace jcx

#endif   /* JCX_PLUGIN_PLUGINCONTAINER_H */
