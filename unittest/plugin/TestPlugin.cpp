#include "gtest/gtest.h"

#include <string>
#include <sstream>
#include <jcx/thread/Thread.h>
#include <jcx/base/Singleton.h>

class IPluginable{
public:
    virtual ~IPluginable(){
    }

    template<typename T> 
    T * as(){
        return dynamic_cast<T*>(this);
    }
};


class IMessageListener {
public:
    virtual ~IMessageListener(){
    }

    virtual int send(const char * data, int len) = 0;
virtual int recv(const char * data, int len) = 0;
};

class IConnectionListener {
public:
    virtual ~IConnectionListener(){
    }

    virtual void beforeConnect(int errCode) = 0;
    virtual void connected(int errCode) = 0;

    virtual void beforeDisconnect(int errCode) = 0;
    virtual void disconnected(int errCode) = 0;
};


class IApi : public IPluginable{
public:   
    virtual ~IApi(){
    }

    virtual int addMessageListener(IMessageListener * msgListener) = 0;
    virtual void removeMessageListener(IMessageListener * msgListener) = 0;
    virtual void clearMessageListener() = 0;

    virtual int addConnectionListener(IConnectionListener * connListener) = 0;
    virtual void removeConnectionListener(IConnectionListener * connListener) = 0;
    virtual void clearConnectionListener() = 0;

    virtual void clearListener() = 0;

    virtual int send(const char * data, int len) = 0;

    virtual int start() = 0;
    virtual void stop() = 0;
};

class AbstractApi : public IApi {
public:
    AbstractApi()
    :_started(false){
    }
    ~AbstractApi() override{
    }
    int addMessageListener(IMessageListener * msgListener) override{
        return 0;
    }
    void removeMessageListener(IMessageListener * msgListener) override {
    }
    void clearMessageListener() override {
    }

    int addConnectionListener(IConnectionListener * connListener) override {
        return 0;
    }
    void removeConnectionListener(IConnectionListener * connListener) override {
    }
    void clearConnectionListener() override {
    }

    void clearListener() override {
    }

    int send(const char * data, int len) override {
        return 0;
    }

    int start() override {
        _started = true;
        return 0;
    }
    void stop() override {
        _started = false;
    }
protected:
    volatile bool _started;    
};


void wait(int sec){
    jcx::thread::Thread::sleep(sec);
}


class PluginManager : public jcx::base::Singleton<PluginManager> {
public:
    PluginManager(){
        _plugin = new AbstractApi();
    }
    ~PluginManager() override {
    }
    IPluginable & findRef(const char * pluginName){
        return  *_plugin;
    }

    void add(IPluginable * plugin){
        //TODO: 
    }
    void remove(IPluginable * plugin){
        //TODO: 
    }

private:
    IPluginable * _plugin;
};

// --------------------------------------------------------------------
class GtpApi : public AbstractApi {
public:
};

TEST(PluginTest, api){
    IApi* api = PluginManager::instance()->findRef("api").as<IApi>();
    ASSERT_TRUE(api != NULL);

    api->addMessageListener(NULL);
    api->addConnectionListener(NULL);

    api->start();

    const char * hello = "helllllllll";
    for( int i = 0; i < 10; i++){
        api->send(hello, strlen(hello));
    }

    wait(1);

    api->stop();

    api->clearListener();
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
