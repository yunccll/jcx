
#ifndef  JCX_PLUGIN_PLUGINCONTAINER_H
#define  JCX_PLUGIN_PLUGINCONTAINER_H


#include <jcx/base/HashMap.h>
#include <jcx/plugin/IPluginable.h>

namespace jcx { 
namespace plugin {

class PluginContainer final {
public:
    PluginContainer();
    ~PluginContainer();

    IPluginable * find(const char * name);

    int add(const char * name, IPluginable * plugin);
    void remove(const char * name);

private:
    jcx::base::HashMapForPtr<IPluginable> _plugins;
};

} //namespace plugin
} //namespace jcx

#endif   /* JCX_PLUGIN_PLUGINCONTAINER_H */
