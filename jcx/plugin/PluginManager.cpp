#include "PluginManager.h"

namespace jcx { 
namespace plugin {

PluginManager::PluginManager(){
}

PluginManager::~PluginManager(){
}

IPluginable * PluginManager::find(const char * name){
    if(name != NULL)
        return  _plugins.get(name);
    return &IPluginable::Null;
}

IPluginable & PluginManager::findRef(const char * name){
    if(name != NULL)
        return *(_plugins.get(name));
     return IPluginable::Null;
}

int PluginManager::add(const char * name, IPluginable * plugin){
    if(name != NULL){
        return _plugins.insertOrReplace(name, plugin);
    }
    return -1;
}
void PluginManager::remove(const char * name){
    if(name != NULL){
        _plugins.remove(name);
    }
}

} //namespace plugin
} //namespace jcx
