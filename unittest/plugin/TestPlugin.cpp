#include "gtest/gtest.h"

#include <string>
#include <sstream>
#include <jcx/thread/Thread.h>
#include <jcx/base/Singleton.h>
#include <algorithm>
#include <vector>
#include <jcx/base/HashMap.h>
#include <jcx/base/Builder.h>


class IPluginable{
public:
    virtual ~IPluginable(){
    }

    template<typename T> 
    T * as(){
        return dynamic_cast<T*>(this);
    }
    static IPluginable Null;
};
IPluginable IPluginable::Null;


class IMessageListener {
public:
    virtual ~IMessageListener(){
    }

    //after send msg
    virtual int send(int errCode, const char * data, int len) = 0;
    //after recv msg
    virtual int recv(int errCode, const char * data, int len) = 0;
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


template<typename T>
class Listeners {
public:
    typedef std::vector<T> ListenerContainer;

    Listeners(){}
    virtual ~Listeners(){}

    int insert(const T & t){
        _listeners.push_back(t);
        return 0;
    }

    void remove(const T & t){
        auto it = std::find(_listeners.begin(), _listeners.end(), t);
        if(it != _listeners.end()){
            _listeners.erase(it);
        }
    }
    void clear(){
        _listeners.clear();
    }
    unsigned long long size() const {
        return _listeners.size();
    }

    /* 
    //TODO: return value ????
    int visit(Caller<bool (T*)> cb){
        auto it  = _listeners.begin();
        for(; it != _listeners.end(); ++it){
            if(false == cb(*it)){
                return -1;
            }
        }
        return 0;
    }*/

    class Iterator {
    public:
        Iterator(ListenerContainer& container)
        : _it(container.begin())
        , _container(container)
        {
        }
        bool hasNext(){
            return _it != _container.end();
        }
        typename ListenerContainer::value_type next(){
            auto tmp = *_it;
            ++_it;
            return tmp;
        }
    private:
        typename ListenerContainer::iterator _it;
        ListenerContainer& _container;
    };

    Iterator iterator(){
        return Iterator(_listeners);
    }
        
private:
    ListenerContainer _listeners;
};

class AbstractApi : public IApi {
public:
    AbstractApi(){
    }
    ~AbstractApi() override{
    }
    int addMessageListener(IMessageListener * msgListener) override{
        if(msgListener != NULL)
            return _msgLisenters.insert(msgListener);
        return -1;
    }
    void removeMessageListener(IMessageListener * msgListener) override {
        _msgLisenters.remove(msgListener);
    }
    void clearMessageListener() override {
        _msgLisenters.clear();
    }

    int addConnectionListener(IConnectionListener * connListener) override {
        if(connListener != NULL)
            return _connListeners.insert(connListener);
        return -1;
    }
    void removeConnectionListener(IConnectionListener * connListener) override {
        _connListeners.remove(connListener);
    }
    void clearConnectionListener() override {
        _connListeners.clear();
    }

    void clearListener() override {
        clearMessageListener();
        clearConnectionListener();
    }


    int send(const char * msg, int len) override{
        int ret = sendImp(msg, len);

        notifyMsgListener(ret, msg, len);
        return ret;
    }

private:
    void notifyMsgListener(int errCode, const char * msg, int len){
        auto it = _msgLisenters.iterator();
        while(it.hasNext()){
            it.next()->send(errCode, msg, len);
        }
    }
   
protected:
    virtual int sendImp(const char * msg, int len) = 0;

protected:
    Listeners<IMessageListener*> _msgLisenters;
    Listeners<IConnectionListener*> _connListeners;
};


void wait(int sec){
    jcx::thread::Thread::sleep(sec);
}


// --------------------------------------------------------------------
class GtpApi : public AbstractApi{
public:
    ~GtpApi() override {
    }
    int start() override {
        return 0;
    }
    void stop() override {
    }

    int sendImp(const char * msg, int len) override {
        return 0;
    }
};

class PluginManager : public jcx::base::Singleton<PluginManager> {
public:
    PluginManager(){
    }
    ~PluginManager() override {
    }
    IPluginable * find(const char * name){
        if(name != NULL)
            return  _plugins.get(name);
        return &IPluginable::Null;
    }

    IPluginable & findRef(const char * name){
        if(name != NULL)
            return *(_plugins.get(name));
         return IPluginable::Null;
    }

    int add(const char * name, IPluginable * plugin){
        if(name != NULL){
            return _plugins.insertOrReplace(name, plugin);
        }
        return -1;
    }
    void remove(const char * name){
        if(name != NULL){
            _plugins.remove(name);
        }
    }

private:
    jcx::base::HashMapForPtr<IPluginable> _plugins;
};





TEST(PluginTest, api){
    auto gtpapi = jcx::base::BuilderSptr<GtpApi>::make();
    PluginManager::instance()->add("api", gtpapi.get());




    //use 
    IApi* api = PluginManager::instance()->find("api")->as<IApi>();
    ASSERT_TRUE(api != NULL);

    api->addMessageListener(NULL);
    api->addConnectionListener(NULL);

    api->start();

    const char * hello = "helllllllll";
    for( int i = 0; i < 10; i++){
        api->send(hello, strlen(hello));
    }

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
