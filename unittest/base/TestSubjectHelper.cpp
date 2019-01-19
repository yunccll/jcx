#include "gtest/gtest.h"
#include <iostream>

#include <jcx/base/SubjectHelper.h>

using namespace jcx;
using namespace base;

class IConnection{
public:
    virtual ~IConnection(){
    }
    virtual int connected(int errcode) = 0;
    virtual int disconnected(int errcode) = 0;
};

class TcpListener : public IConnection {
public:
    virtual ~TcpListener(){
    }
    int connected(int errcode){
        std::cout << "tcp listener connected" << std::endl;
        return 0;
    }
    int disconnected(int errcode){
        std::cout << "tcp listener disconnected" << std::endl;
        return 0;
    }
};

class TcpConnecter : public SubjectHelper::One<IConnection, TcpConnecter>{
public:
    TcpConnecter() {}
    TcpConnecter(IConnection * listener)
    :SubjectHelper::One<IConnection, TcpConnecter>(listener)
    {
    }
    virtual ~TcpConnecter(){}

    int connected(int errcode){
        auto l = getListener();
        if(l){
            return l->connected(errcode);
        }
        return -1;
    }
    int disconnected(int errcode){
        auto l = getListener();
        if(l){
            return l->disconnected(errcode);
        }
        return -1;
    }
private:
};

TEST(SubjectHelperTest, OneSubjectToOneListener){
    TcpListener tl;
    TcpConnecter con(&tl);  //inject

    con.connected(0);
    con.disconnected(0);
}

TEST(SubjectHelperTest, OneSubjectToOneListener1){
    TcpConnecter con;

    TcpListener tl;
    con.attach(&tl);

    con.connected(0);
    con.disconnected(0);

    con.detach();
}





class TcpConnecterMany : public SubjectHelper::Many<IConnection, TcpConnecterMany> {
public:
    virtual ~TcpConnecterMany(){
    }

    int connected(int errcode){
        auto it = iterator();
        while(it.hasNext()){
            it.next()->connected(errcode);
            //it.next();
        }
        return 0;
    }
    int disconnected(int errcode){
        auto it = iterator();
        while(it.hasNext()){
            it.next()->disconnected(errcode);
            //it.next();
        }
        return 0;
    }
};

TEST(SubjectHelperTest, oneSubjectToManyListener){
    TcpConnecterMany many;

    auto l = new TcpListener();
    auto l1 = new TcpListener();
    auto l2 = new TcpListener();

    many.attach(l).attach(l1).attach(l2);

    many.connected(0);
    many.disconnected(0);

    many.detach(l2).detach(l1).detach(l);

    delete l2;
    delete l1;
    delete l;
}
