
#ifndef  JCX_PLUGIN_PLUGINMANAGER_H
#define  JCX_PLUGIN_PLUGINMANAGER_H

#include <jcx/base/Singleton.h>
#include <jcx/base/HashMap.h>
#include <jcx/plugin/IPluginable.h>

namespace jcx { 
namespace plugin {

class PluginManager : public jcx::base::Singleton<PluginManager> {
public:
    PluginManager();
    ~PluginManager() override ;

    IPluginable * find(const char * name);
    IPluginable & findRef(const char * name);

    int add(const char * name, IPluginable * plugin);
    void remove(const char * name);

private:
    jcx::base::HashMapForPtr<IPluginable> _plugins;
};

} //namespace plugin
} //namespace jcx

#endif   /* PLUGINMANAGER_H */
