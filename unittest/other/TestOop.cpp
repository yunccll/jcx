#include "gtest/gtest.h"

#include <jcx/base/TestCaseHelper.h>

using namespace jcx;
using namespace base;

//Note: about the operator override
//  thinking:  A a ;  B b; ==>  what is the type of a + b ?
//  so reasonable statement is :  
//      A a1;  A a2 ==> a1 + a2 OK;
//      SubA  sa1;  SubA sa2 ==>  sa1 + sa2 OK  because (SuA operator +(const SubA &))
//      sa1 + a1 ==> forbid !!!!! ==> sa1 no operator +(const A &) compile error
//      a1 + sa1 ==> OK ;  a1 + sa1 ===> a1 + (cosnt A&)sa1 ==> OK

TEST(OopTest, operatorDerive){
   _Sub s1 ; 
   _Sub s2 ;

   ASSERT_FALSE(s1 == s2);

   s2 = s1;
   ASSERT_TRUE(s1 == s2);
}


class Oop_Sub : public _Base{
public:
    Oop_Sub(){
        static int sid = 0;
        _sid = sid++;
        printf("Oop_Sub constructor\n");
    }
    ~Oop_Sub(){
        printf("Oop_Sub destructor\n");
    }
    /*
    bool operator == (const _Base & right) const{
        return _Base::operator ==(right);
    }
    bool operator == (const Oop_Sub & right) const{
        return _Base::operator ==(right) && _sid == right._sid;
    }*/
    void setSid(const int sid){
        _sid = sid;
    }
    const int getSid() const {
        return _sid;
    }
private:
    int _sid;
};



TEST(OopTest, oopSub_cmp_Base){
        Oop_Sub  os1 ;
        _Base b3;
        ASSERT_FALSE(os1 == b3);

        b3.setId(os1.id());
        ASSERT_TRUE(os1 == b3);
}
TEST(OopTest, oopSub_cmp_oopSub){
    Oop_Sub os1;
    Oop_Sub os2;
    ASSERT_FALSE(os1 == os2);
}

class OopSubSub : public Oop_Sub{
public:
    bool operator == (const OopSubSub & right) const{
        return _Base::operator ==(right);
    }
};

TEST(OopTest, oopSubSub_cmp_oopSubSub){
    OopSubSub oss1;
    OopSubSub oss2;
    ASSERT_FALSE(oss1 == oss2);

    _Base b1;
    ASSERT_FALSE(b1 == oss1);

//    ASSERT_FALSE(oss1 == b1); compile error:  oos1 has no operator == (const _Base &) const;
}
