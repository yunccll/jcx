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
#include <ostream>
#include <boost/log/core.hpp>

#include <boost/log/sources/severity_logger.hpp>        // severity_logger

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp> //BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT

//#include <boost/move/utility_core.hpp>
//#include <boost/log/sources/record_ostream.hpp>

#include <boost/log/trivial.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/attributes.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace src = boost::log::sources;
namespace attrs = boost::log::attributes;



/* 
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
    BOOST_LOG_TRIVIAL(info) << "info : hello world" ;
    BOOST_LOG_TRIVIAL(warning) << "warning : hello world" ;
    BOOST_LOG_TRIVIAL(error) << "error : hello world" ;
    BOOST_LOG_TRIVIAL(fatal) << "fatal : hello world" ;
}

TEST(BoostLog, continueUse){
    BOOST_LOG_TRIVIAL(trace) << "trace : Hello World" ;
    BOOST_LOG_TRIVIAL(debug) << "debug : hello world" ;
    BOOST_LOG_TRIVIAL(info) << "info : hello world" ;
    BOOST_LOG_TRIVIAL(warning) << "warning : hello world" ;
    BOOST_LOG_TRIVIAL(error) << "error : hello world" ;
    BOOST_LOG_TRIVIAL(fatal) << "fatal : hello world" ;
}



BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt); 
TEST(BoostLog, globalLogger){
    src::logger_mt & lg = my_logger::get();
    BOOST_LOG(lg) << "Hello World";
}

*/


enum severity_level {
    normal,
    notification,
    warning,
    error,
    critical,
};


template<typename CharT, typename Traits> 
inline std::basic_ostream<CharT, Traits> & operator<<(
    std::basic_ostream<CharT, Traits> & os, severity_level lvl){
     static const char* const str[] =
     {
         "normal",
         "notification",
         "warning",
         "error",
         "critical"
     };
     if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
         os << str[lvl];
     else
         os << static_cast< int >(lvl);
     return os;
}

/*  
BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(scope, "Scope", attrs::named_scope::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(timeline, "Timeline", attrs::timer::value_type)
*/

TEST(BoostLog, severityLevelLogger){
    logging::add_file_log(
        keywords::file_name = "main_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%] [%LineID%] [%TimeLine%] [%Tag%] %Message%"
    );

    ///BOOST_LOG_NAMED_SCOPE("named_scope_logging");
    src::severity_logger<severity_level> slog;

    slog.add_attribute("Tag", attrs::constant<std::string>("My tag value"));
    slog.add_attribute("LineID",  attrs::counter< unsigned int >(1));
    slog.add_attribute("TimeStamp",  attrs::local_clock());
    slog.add_attribute("TimeLine",  attrs::timer());


    BOOST_LOG_SEV(slog, normal) << "Normal Hello world";
    BOOST_LOG_SEV(slog, notification) << "Notification Hello world";
}
