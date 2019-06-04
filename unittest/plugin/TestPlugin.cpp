#include "gtest/gtest.h"

#include "GtpApi.h"

#include <jcx/base/Builder.h>
#include <jcx/plugin/PluginContainer.h>
#include <jcx/base/Singleton.h>
#include <jcx/base/Iterator.h>


class IDbConnection  : public jcx::plugin::IPluginable {
public:
    ~IDbConnection() override {}
    virtual void transaction() = 0;
    virtual void execute() = 0;
    virtual void commit() = 0;
    virtual void rollback() = 0;
    virtual void close() = 0;
};

class MysqlConnection : public IDbConnection {
public:
    MysqlConnection(){}
    ~MysqlConnection()override {}
    void transaction() override {
        std::cout << "mysql transactions start" << std::endl;
    }
    void execute() override {
        std::cout << "mysql execute" << std::endl;

    }
    void commit() override {
        std::cout << "mysql commit" << std::endl;
    }
    void rollback() override {
        std::cout << "mysql rollback" << std::endl;
    }
    void close() override {
        std::cout << "mysql close" << std::endl;
    }
};

class AppConfig : public jcx::base::Singleton<AppConfig>{
public:
    ~AppConfig() override {
        freePlugins();
    }

    jcx::plugin::IPluginable * api(){
        return new GtpApi();
    }
    jcx::plugin::IPluginable * mysql(){
        return new MysqlConnection();
    }
    int loadPlugins(){
        _plugins.add("api", api());
        _plugins.add("db", mysql());
        return 0;
    }

    auto plugins(){
        return &_plugins;
    }

private:
    void freePlugins(){
        auto it = _plugins.iterator();
        while(it.hasNext()){
            auto & v= it.next();
            delete v.second;
        }
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




TEST(PluginTest, DbConnection){
    IDbConnection * db = AppConfig::instance()->plugins()->find("db")->as<IDbConnection>();
    ASSERT_TRUE(db != NULL);

    db->transaction();
    db->execute();
    db->commit();
    db->rollback();
    db->close();
}
