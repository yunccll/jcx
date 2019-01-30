#include "gtest/gtest.h"

#include <iostream>
#include <jcx/perf/OneShotRecorder.h>
#include <jcx/perf/CodeBlock.h>

TEST(OneShotRecorderTest, use){

    jcx::perf::OneShotRecorder er;
    {
        jcx::perf::CodeBlock cb(er, "forLoop");
        usleep(5000); //5ms
    }
    ASSERT_TRUE(5000 < er.us());
    std::cout << er.toString() << std::endl;
}




#include <jcx/perf/MultiRoundElapseRecorder.h>
TEST(MultiRoundElapseRecorderTest, use){
    jcx::perf::MultiRoundElapseRecorder er("TimeElapseTest.MultiRoundElapseRecorder"); 
    {
        jcx::perf::CodeBlock cb(er, "name1");
        for( int i = 0; i < 10 ;  ++i){
            {
                jcx::perf::CodeBlock cb(er, "loop_i");
                usleep(3000);//3ms
            }
        }
    }
    ASSERT_TRUE(11 == er.rounds());
    ASSERT_TRUE(3000*10 < er.us());
    std::cout << er.toString() << std::endl;
}





#include <jcx/perf/MultiShotRecorder.h>
TEST(MultiShotRecorderTest, use){
    jcx::perf::MultiShotRecorder recorder ; 
    {
        jcx::perf::CodeBlock cb(recorder, "name1");
        for( int i = 0; i < 10 ;  ++i){
            {
                jcx::perf::CodeBlock iloop(recorder, "loop_i");
                usleep(3000);//3ms

                for( int j = 0 ; j < 22; ++j){
                    jcx::perf::CodeBlock jloop(recorder, "loop_j");
                    usleep(1000); //1ms
                }
            }
        }
    }
    std::cout << recorder.toString() << std::endl;
}

