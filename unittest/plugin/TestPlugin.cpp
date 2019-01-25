#include "gtest/gtest.h"

#include "GtpApi.h"

#include <jcx/base/Builder.h>
#include <jcx/plugin/PluginContainer.h>
#include <jcx/base/Singleton.h>


class AppConfig : public jcx::base::Singleton<AppConfig>{
public:
    ~AppConfig() override {
        freePlugins();
    }

    jcx::plugin::IPluginable * api(){
        return new GtpApi();
    }
    auto loadPlugins(){
        _plugins.add("api", api());
        return &_plugins; 
    }

    auto plugins(){
        return &_plugins;
    }

private:
    void freePlugins(){
        //TODO: Iterator -->From HashMap ????
    }
private:
    jcx::plugin::PluginContainer _plugins;
};

TEST(PluginTest, api){

    AppConfig::instance()->loadPlugins();

    //use 
    IApi* api = AppConfig::instance()->plugins()->find("api")->as<IApi>();
    ASSERT_TRUE(api != NULL);

    api->messageSubject().attach(NULL);
    api->connectionSubject().attach(NULL);

    api->start();

    const char * hello = "helllllllll";
    for( int i = 0; i < 10; i++){
        api->send(hello, strlen(hello));
    }

    api->stop();
}


/*  
TEST(PluginTest, DbConnection){
    IDbConnection * db = PluginManager::instance()->findRef("api").as<IDbConnection>();
    ASSERT_TRUE(db != NULL);

    db.transaction();
    db.execute(sql);
    db.commit();
    db.rollback();
    db.close();
}
*/
