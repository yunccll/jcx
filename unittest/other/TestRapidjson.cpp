#include "gtest/gtest.h"
#include <jcx/base/Crossplatform.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>


using namespace rapidjson;
using namespace std;

TEST(RapidjsonTest, use){
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);

    Value& s = d["stars"];
    ASSERT_EQ(10, s.GetInt());
    s.SetInt(s.GetInt() + 1);
    ASSERT_EQ(11, s.GetInt());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    std::cout << buffer.GetString() << std::endl;
}

/* 
TEST(RapidjsonTest, useFile){
    //output the stream
    const char* fn = "RapidjsonTest.cfg";
    {
        const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
        ofstream output(fn);
        ASSERT_TRUE(output.is_open());
        output << json;
    }

    ifstream input(fn, ios::binary|ios::in);
    char buf[1024];
    input.read(buf, sizeof(buf));
    
    Document d;
    d.Parse(buf);

    Value& s = d["stars"];
    ASSERT_EQ(10, s.GetInt());
    s.SetInt(s.GetInt() + 1);
    ASSERT_EQ(11, s.GetInt());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    std::cout << buffer.GetString() << std::endl;
}

TEST(RapidjsonTest, useIfstream){
    const char* fn = "RapidjsonTest.cfg";
    {
        const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
        ofstream output(fn);
        ASSERT_TRUE(output.is_open());
        output << json;
    }
    {
        std::ifstream ifs(fn); 
        if(ifs){
            rapidjson::IStreamWrapper isw(ifs);
            rapidjson::Document d;
            d.ParseStream(isw);
            Value & v = d["project"];
            ASSERT_TRUE(v.IsString());
            ASSERT_STREQ("rapidjson", v.GetString());
            std::cout << "project:" << v.GetString() << std::endl;

            v = d["stars"];
            ASSERT_TRUE(v.IsInt());
            ASSERT_EQ(10, v.GetInt());
            std::cout << "stars:" << v.GetInt() << std::endl;
        }
    }
}

TEST(RapidjsonTest, useOfstream){
    const char* fn = "output.json";
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);

    {
        std::ofstream ofs(fn);
        if(ofs){
            rapidjson::OStreamWrapper osw(ofs);
            Writer<rapidjson::OStreamWrapper> writer(osw);
            d.Accept(writer);
        }
    }
    {
        fn  = "pretty.output.json";
        std::ofstream ofs(fn);
        if(ofs){
            rapidjson::OStreamWrapper osw(ofs);
            PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
            d.Accept(writer);
        }
    }
}*/
