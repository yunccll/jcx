#include "gtest/gtest.h"
#include <jcx/logger/LogLevel.h>
#include <memory>

using namespace jcx;
using namespace logger;


TEST(LogLevelTest, make){
    static const char * de_levelNameTab [] ={
        "Default FATAL",
        "Default ERROR",
        "Default WARN ",
        "Default DEBUG",
        "Default INFO ",
        "Default NOTE ",
        "Default MONI ",        
    };
    auto lvl = std::shared_ptr<LogLevel>(LogLevel::make(de_levelNameTab));
    ASSERT_TRUE(lvl->getCurrentLevel() == LogLevel::INFO);

    ASSERT_TRUE(lvl->getName(LogLevel::INFO) != NULL);
    ASSERT_STREQ(de_levelNameTab[LogLevel::INFO], lvl->getName(LogLevel::INFO));
    ASSERT_STREQ(de_levelNameTab[LogLevel::FATAL], lvl->getName(LogLevel::FATAL));
    ASSERT_STREQ(de_levelNameTab[LogLevel::ERROR], lvl->getName(LogLevel::ERROR));
    ASSERT_STREQ(de_levelNameTab[LogLevel::WARN], lvl->getName(LogLevel::WARN));
    ASSERT_STREQ(de_levelNameTab[LogLevel::DEBUG], lvl->getName(LogLevel::DEBUG));
    ASSERT_STREQ(de_levelNameTab[LogLevel::NOTE], lvl->getName(LogLevel::NOTE));
    ASSERT_STREQ(de_levelNameTab[LogLevel::MONI], lvl->getName(LogLevel::MONI));
}

TEST(LogLevelTest, getName){
    auto lvl = std::shared_ptr<LogLevel>(LogLevel::make());
    ASSERT_TRUE(lvl->getCurrentLevel() == LogLevel::INFO);
    
    ASSERT_TRUE(lvl->getName(LogLevel::INFO) != NULL);
    ASSERT_STREQ("INFO ", lvl->getName(LogLevel::INFO));
    ASSERT_STREQ("FATAL", lvl->getName(LogLevel::FATAL));
    ASSERT_STREQ("ERROR", lvl->getName(LogLevel::ERROR));
    ASSERT_STREQ("WARN ", lvl->getName(LogLevel::WARN));
    ASSERT_STREQ("DEBUG", lvl->getName(LogLevel::DEBUG));
    ASSERT_STREQ("NOTE ", lvl->getName(LogLevel::NOTE));
    ASSERT_STREQ("MONI ", lvl->getName(LogLevel::MONI));

}

TEST(LogLevelTest, curLevel){
    auto lvl = std::shared_ptr<LogLevel>(LogLevel::make());

    ASSERT_TRUE(lvl->getCurrentLevel() == LogLevel::INFO);
    ASSERT_FALSE(lvl->setCurrentLevel(LogLevel::MAX));

    ASSERT_TRUE(lvl->getCurrentLevel() == LogLevel::INFO);

    ASSERT_TRUE(lvl->setCurrentLevel(LogLevel::FATAL));
    ASSERT_TRUE(lvl->getCurrentLevel() == LogLevel::FATAL);
}

TEST(LogLevelTest, canShow){
    auto lvl = std::shared_ptr<LogLevel>(LogLevel::make());

    ASSERT_TRUE(lvl->getCurrentLevel() == LogLevel::INFO);

    ASSERT_FALSE(lvl->canShow(LogLevel::MAX));
    ASSERT_FALSE(lvl->canShow(LogLevel::MONI));
    ASSERT_FALSE(lvl->canShow(LogLevel::NOTE));

    ASSERT_TRUE(lvl->canShow(LogLevel::INFO));
    ASSERT_TRUE(lvl->canShow(LogLevel::DEBUG));
    ASSERT_TRUE(lvl->canShow(LogLevel::WARN));
    ASSERT_TRUE(lvl->canShow(LogLevel::ERROR));
    ASSERT_TRUE(lvl->canShow(LogLevel::FATAL));
}
