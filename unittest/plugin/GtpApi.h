
#ifndef  GTPAPI_H
#define  GTPAPI_H


class IMessageListener {
public:
    virtual ~IMessageListener(){
    }

    //after send msg
    virtual int send(int errCode, const char * data, int len) = 0;
    //after recv msg
    virtual int recv(int errCode, char * data, const int len) = 0;
};



#include <jcx/base/SubjectHelper.h>
class MessageSubject : public jcx::base::SubjectHelper::Many<IMessageListener, MessageSubject> {
public:
    void notifySend(int errCode, const char * msg, int len){
        auto it = iterator();
        while(it.hasNext()){
            it.next()->send(errCode, msg, len);
        }
    }
    void notifyRecv(int errCode, char * msg, const int len){
        auto it = iterator();
        while(it.hasNext()){
            it.next()->recv(errCode, msg, len);
        }
    }
};

class IConnectionListener {
public:
    virtual ~IConnectionListener(){
    }

    virtual void beforeConnect(const char * ip, const int port) = 0;
    virtual void connected(int errCode, const char * ip, const int port) = 0;

    virtual void beforeDisconnect(const char * ip, const int port) = 0;
    virtual void disconnected(int errCode, const char * ip, const int port) = 0;
};
class ConnectionSubject : public jcx::base::SubjectHelper::Many<IConnectionListener, ConnectionSubject> {
public:

    void notifyBeforeConnect(const char * ip, const int port){
        auto it = iterator();
        while(it.hasNext()){
            it.next()->beforeConnect(ip, port);
        }
    }
    void notifyConnected(int errCode, const char * ip, const int port){
        auto it = iterator();
        while(it.hasNext()){
            it.next()->connected(errCode, ip, port);
        }
    }

    void notifyBeforeDisconnect(const char * ip, const int port){
        auto it = iterator();
        while(it.hasNext()){
            it.next()->beforeDisconnect(ip, port);
        }
    }
    void notifyDisconnected(int errCode, const char * ip, const int port){
        auto it = iterator();
        while(it.hasNext()){
            it.next()->disconnected(errCode, ip, port);
        }
    }
};



#include <jcx/plugin/IPluginable.h>
class IApi : public jcx::plugin::IPluginable{
public:   
    virtual ~IApi(){
    }

    virtual MessageSubject & messageSubject() = 0;
    virtual ConnectionSubject & connectionSubject() = 0;

    virtual int send(const char * data, int len) = 0;

    virtual int start() = 0;
    virtual void stop() = 0;
    virtual int recv(char * data, const int capacity) = 0;
};

class AbstractApi : public IApi {
public:
    AbstractApi(){
    }
    ~AbstractApi() override{
    }

    int send(const char * msg, int len) override{
        int ret = sendImp(msg, len);
        _msgSubject.notifySend(ret, msg, len);
        return ret;
    }

    int recv(char * msg, const int capacity) override {
        int ret = recvImp(msg, capacity);
        _msgSubject.notifyRecv(ret, msg, capacity); 
        return ret;
    }

    MessageSubject & messageSubject() override {
        return _msgSubject;
    }

    //TODO: connected, disconnected,.....
    ConnectionSubject & connectionSubject() override {
        return _connSubject;
    }

protected:
    virtual int sendImp(const char * msg, int len) = 0;
    virtual int recvImp(char * msg, const int capacity) = 0;

protected:
    MessageSubject _msgSubject;
    ConnectionSubject _connSubject;
};



// --------------concrete Api imp------------------------------------------------------
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
    int recvImp(char * msg, const int capacity) override {
        return 0;
    }
};


#endif   /* GTPAPI_H */
