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

#include <boost/log/utility/setup/console.hpp>  //add_console_log


#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>        // severity_logger
#include <boost/log/utility/manipulators/to_log.hpp>

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp> //BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT

//#include <boost/move/utility_core.hpp>
//#include <boost/log/sources/record_ostream.hpp>

#include <boost/log/trivial.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/attributes.hpp>
#include <boost/log/support/date_time.hpp>


namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace src = boost::log::sources;
namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;



/* 
void init(){
    //set sink 
    //logging::add_file_log("main.log");
    logging::add_file_log(
        keywords::file_name = "main_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%] [%LineID%] [%Severity%] %Message%"
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



enum severity_level11 {
    normal,
    notification,
    warning,
    error,
    critical,
};

template<typename CharT, typename Traits> 
inline std::basic_ostream<CharT, Traits> & operator<<(
    std::basic_ostream<CharT, Traits> & os, severity_level11 lvl){
     static const char* const str[] = {
         "NORMAL",
         "NOTIFICATION",
         "WARNIng",
         "ERROR",
         "CRITIcal"
     };
     if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
         os << str[lvl];
     else
         os << static_cast< int >(lvl);
     return os;
}

//logging::formatting_ostream& operator<<
//(
//    logging::formatting_ostream& strm,
//    logging::to_log_manip< severity_level11, tag::severity > const& manip
//)
//{
//    static const char* strings[] =
//    {
//        "NORM",
//        "NTFY",
//        "WARN",
//        "ERRR",
//        "CRIT"
//    };
//
//    severity_level11 level = manip.get();
//    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
//        strm << strings[level];
//    else
//        strm << static_cast< int >(level);
//
//    return strm;
//}



// * for log 's format 
BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)

BOOST_LOG_ATTRIBUTE_KEYWORD(scope, "Scope", attrs::named_scope::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(timeline, "Timeline", attrs::timer::value_type)

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level11) 




BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)

TEST(BoostLog, severityLevelLogger){

    logging::add_console_log(std::clog, keywords::format = "[%TimeStamp%]: %_%");

    logging::add_file_log(
        keywords::file_name = "main_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
//        keywords::format = "[%TimeStamp%] [%LineID%] [%Severity%] %Message%"

        keywords::format = expr::stream
            << expr::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f")
            << " [" << expr::format_date_time(timeline, "%O:%M:%S")
            << "] [" << expr::format_named_scope(scope, keywords::format = "%n (%f:%l)")
            << "] [" << tag_attr 
            << "] <" << severity
            << "> " << expr::message

    );

    src::logger lg;
    BOOST_LOG(lg) <<  "only message" ; //only  message

    logging::add_common_attributes(); // for timestamp, lineId, process_id, thread_id

    BOOST_LOG(lg) <<  "only common message" ; // add common message

    logging::core::get()->add_thread_attribute("Scope", attrs::named_scope()); //for scope attr
    BOOST_LOG_FUNCTION();   // for scope 's function & line id 

    BOOST_LOG(lg) <<  "function & file & line no" ; // add function & file & line no


    src::severity_logger< severity_level11 > slg;
    slg.add_attribute("Timeline", attrs::timer()); //add my timeline attribute for the log source
    slg.add_attribute("Tag", attrs::constant<std::string>("chenglun")); // add my tag attribute for the log source

    BOOST_LOG_SEV(slg, normal) << "severity log: A regular message";
    BOOST_LOG_SEV(slg, warning) << "severity log: Something bad is going on but I can handle it";
    BOOST_LOG_SEV(slg, critical) << "severity log: Everything crumbles, shoot me now!";
}




//TEST(BoostLog, severityLevelLogger){
//
//    logging::add_file_log(
//        keywords::file_name = "main.log",
//        keywords::rotation_size = 10 * 1024 * 1024,
//        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
//        keywords::open_mode = std::ios::out | std::ios::app,
//        keywords::format = "[%TimeStamp%] [%LineID%] [%TimeLine%] [%Tag%] [%Severity%] %Message%"
//    );
//
//    ///BOOST_LOG_NAMED_SCOPE("named_scope_logging");
//    src::severity_logger<severity_level11> slog;
//
//
//    logging::core::get()->set_filter(expr::attr< severity_level11>("Severity") >= notification);
//
//    slog.add_attribute("LineID",  attrs::counter< unsigned int >(1));
//    slog.add_attribute("TimeStamp",  attrs::local_clock());
//    slog.add_attribute("TimeLine",  attrs::timer());
//    slog.add_attribute("Tag", attrs::constant<std::string>("My tag value"));
//
//
//    BOOST_LOG_SEV(slog, normal) << "normal Hello world";
//    BOOST_LOG_SEV(slog, notification) << "notification Hello world";
//    BOOST_LOG_SEV(slog, warning) << "warning Hello world";
//    BOOST_LOG_SEV(slog, error) << "error Hello world";
//    BOOST_LOG_SEV(slog, critical) << "critical Hello world";
//}
