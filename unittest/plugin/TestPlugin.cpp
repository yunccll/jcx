#include "gtest/gtest.h"

#include "GtpApi.h"

#include <jcx/base/Builder.h>
#include <jcx/plugin/PluginManager.h>



TEST(PluginTest, api){
    auto gtpapi = jcx::base::BuilderSptr<GtpApi>::make();
    jcx::plugin::PluginManager::instance()->add("api", gtpapi.get());

    //use 
    IApi* api = jcx::plugin::PluginManager::instance()->find("api")->as<IApi>();
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
