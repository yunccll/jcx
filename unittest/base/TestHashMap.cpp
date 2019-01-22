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
    auto hash = new HashMapForPtr<void>();


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

TEST(HashMap, toPtr){
    IMapForPtr<void>  * hash = new HashMapForPtr<void>();
    hash->insert("hello", NULL);
    hash->insertOrReplace("hello1", NULL);

    if(hash->contains("hello")){
        ASSERT_TRUE(NULL == hash->getRef("hello"));
    }

    ASSERT_TRUE(false == hash->contains("hhhh"));
    hash->getRef("hhhh"); //Note: ????
    ASSERT_TRUE(true == hash->contains("hhhh"));


    char * name  = new char[10] ;
    memset(name, 0, 10);
    strncpy(name, "chenglun", 10);
    ASSERT_TRUE(strcmp(name, "chenglun") == 0);

    hash->insert(name, NULL);

    ASSERT_TRUE(hash->contains(name));
    ASSERT_TRUE(hash->contains("chenglun"));
    delete [] name;

    ASSERT_TRUE(hash->contains("chenglun"));
    const char * str = "chenglun";
    ASSERT_TRUE(NULL == hash->get(str));

    delete hash;
}

