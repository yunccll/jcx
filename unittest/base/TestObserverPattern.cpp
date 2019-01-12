#include "gtest/gtest.h"
#include <iostream>

#include <jcx/base/Caller.h>
#include <jcx/base/Builder.h>
#include <jcx/base/Event.h>

using namespace jcx;
using namespace base;

static void f(Event * ev){
    std::cout << "event:" << ev->toString() << std::endl;
}
TEST(ObserverTest, callback){
    Caller1<void, Event*> caller(&f);
    {
        auto ev = BuilderPtr<Event>::make(1, (void*)NULL);
        caller(ev);
        delete ev;

        auto ev_auto = BuilderSptr<Event>::make(2, (void*)NULL);
        caller(ev_auto.get());
    }
}

/*  
TEST(ObserverTest, listener){
    TestSubject sub;

    auto listener = Listener::makeAuto();

    sub.attach(listener);
    sub.notify(Event::makeAuto(1, NULL));
    sub.detach(listener);
}
TEST(ObserverTest, observer){
    TestSubject  sub;
    {
        auto obs = TestObserver::makeAuto(1);
        sub.attach(obs);
        sub.notify(Event::makeAuto(1, NULL));
        sub.detach(obs);
    }
}



class ConnectCallback {
public:
    ConnectCallback(const char * ip, int port)
    :_ip(ip),
    _port(port){

    }
    ~ConnectCallback(){
    }
    static int connected(int errcode){
        std::cout << "ip:" << _ip << ", port:" << _port
            << " connected:" << errcode 
            << std::endl;
    }
private:
    std::string _ip;
    int _port;
}

TEST(ObserverTest, callback2){
    Functor<int, int> func(&ConnectCallback::connected);
    TcpConnecter<int, int> connecter(func);
    connecter.connected(0);
}



TEST(ObserverTest, listener1){
    TcpConnecter connecter; // connected, disconnected

    auto listener = ConnectionListener::makeAuto();

    connecter.inject(listener); //move to config
    connecter.connected();
    connecter.eject(listener);
}

TEST(ObserverTest, observer){
    TcpConnecter connecter;
    auto connecterObserver = ConnecterObserver::makeAuto();
    connecter.attach(connecterObserver);
    connecter.notify(ConnectEvent::makeAuto());
    connecter.detach(connecterObserver);
}
*/
