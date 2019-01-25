#include "PluginContainer.h"

namespace jcx { 
namespace plugin {

PluginContainer::PluginContainer(){
}

PluginContainer::~PluginContainer(){
}

IPluginable * PluginContainer::find(const char * name){
    if(name != NULL) return  _plugins.get(name);
    return &IPluginable::Null;
}

int PluginContainer::add(const char * name, IPluginable * plugin){
    if(name != NULL){
        return _plugins.insertOrReplace(name, plugin);
    }
    return -1;
}
void PluginContainer::remove(const char * name){
    if(name != NULL){
        _plugins.remove(name);
    }
}

} //namespace plugin
}//namespace jcx
