#include "gtest/gtest.h"
#include <jcx/base/HashMap.h>
#include <jcx/base/Builder.h>

#include <string>

using namespace jcx;
using namespace base;



TEST(HashMap, test){
    auto  hash = new HashMap<int, int>();
    hash->insert(1, 1);
    ASSERT_TRUE(hash->size() == 1);

    hash->remove(1);
    ASSERT_TRUE(hash->size() == 0); 
    hash->insert(1, 1);
    hash->insert(2, 1);
    ASSERT_TRUE(hash->size() == 2);

    hash->clear();
    ASSERT_TRUE(hash->size() == 0);
    delete hash;
}


TEST(HashMap, test_str){
    auto hash = BuilderSptr< HashMap<const char *, int> >::make();

    hash->insert("100", 1);
    ASSERT_TRUE(1 == hash->get("100"));
    ASSERT_TRUE(1 == hash->get("100"));

    hash->insertOrReplace("100", 2);
    ASSERT_TRUE(2 == hash->getRef("100"));
}

TEST(HashMap, test_ptr){

    char * ptr = NULL;
    auto hash = new HashMapForPtr();


    hash->insert("hello", ptr);
    hash->insert("hello2", ptr);
    ASSERT_TRUE(ptr == hash->get("hello"));
    ASSERT_TRUE(ptr == hash->getRef("hello"));

    
    {  //Test getValue
        int a ;
        void * refPtr = &a;
        ASSERT_TRUE(true == hash->getValue("hello",refPtr));
        ASSERT_TRUE(refPtr == ptr);

        refPtr = &a;
        ASSERT_TRUE(false == hash->getValue("hl", refPtr));
        ASSERT_TRUE(refPtr == &a);
    }


    char * ptr1 = NULL;

    hash->set("hello", ptr1);
    ASSERT_TRUE(ptr1 == hash->get("hello"));
}

TEST(HashMap, interface){
    IMap<const char * , void *>  * hash = new HashMapForPtr();
    hash->insert("hello", NULL);

    if(hash->contains("hello")){
        ASSERT_TRUE(NULL == hash->getRef("hello"));
    }

    ASSERT_TRUE(false == hash->contains("hhhh"));
    hash->getRef("hhhh"); //Note: ????
    ASSERT_TRUE(true == hash->contains("hhhh"));

    delete hash;
}


/*  
 *  TODO:  refactor to easy use [Note: don't use the template heavily]
TEST(HashMapPtr, ptr){
    {
        auto hash = new HashMap<int>();
        
        hash->insert("string", 1);
        hash->get("string");
        hash->set("string", 2);
        hash->size();
        hash->remove("string");

        hash->visit([](....));
        it = has->getIterator();
        for(it->hasNext()){
            it->next();
        }

        hash->visit(caller<bool,int*> cb);
    }

    {
        auto hash = new HashMapPtr<int>();

        hash->insert("string", new int(1));
        hash->get("string");
        hash->set("string", new int(3))
        hash->size();
        hash->remove("string");

        auto it = hash->iterator();
        while(it->hashNext()){
            it->next<int>();
        }

        hash->visit(caller<bool,int*> cb);
    }
}
*/
