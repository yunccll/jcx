/*
 *  Copyright 2019, Cheng Lun.  All right reserved.
 *
 *  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF Cheng Lun.
 *  LTD.  THE CONTENTS OF THIS FILE MAY NOT BE DISCLOSED TO THIRD
 *  PARTIES, COPIED OR DUPLICATED IN ANY FORM, IN WHOLE OR IN PART,
 *  WITHOUT THE PRIOR WRITTEN PERMISSION OF Cheng Lun.
 *
 *
 *  Edit History:
 *
 *    2019年06月24日 - Created by Cheng Lun yunccll@sina.com
 *
 */


#include "gtest/gtest.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

void init(){
    //set sink 
    //logging::add_file_log("main.log");
    logging::add_file_log(
        keywords::file_name = "main_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%] [%LineID%] %Message%"
    );
    //set level
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
    logging::add_common_attributes();
}



TEST(BoostLog, use){
    init();

    BOOST_LOG_TRIVIAL(trace) << "trace : Hello World" ;
    BOOST_LOG_TRIVIAL(debug) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(info) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(warning) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(error) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(fatal) << "debug : hello world" ;
}

TEST(BoostLog, continueUse){
    BOOST_LOG_TRIVIAL(trace) << "trace : Hello World" ;
    BOOST_LOG_TRIVIAL(debug) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(info) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(warning) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(error) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(fatal) << "debug : hello world" ;
}
