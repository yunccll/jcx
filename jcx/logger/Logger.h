#ifndef  JCX_LOGGER_LOGGER_H
#define  JCX_LOGGER_LOGGER_H

#include <jcx/logger/LoggerProxy.h>
//TODO: test the macro interface only in single ut_file
#define LOG_INFO(fmt, ...)  do {\
    const jcx::logger::Info info = {__FILE__, __LINE__, __func__}; \
    jcx::logger::LoggerProxy * logger = jcx::logger::LoggerProxy::instance(); \
    logger->varInfo(&info, fmt, ##__VA_ARGS__); \
    logger->flush();\
} while (0)

#define LOG_DEBUG(fmt, ...)  do {\
    const jcx::logger::Info info = {__FILE__, __LINE__, __func__}; \
    jcx::logger::LoggerProxy * logger = jcx::logger::LoggerProxy::instance(); \
    logger->varDebug(&info, fmt, ##__VA_ARGS__); \
    logger->flush();\
} while (0)

#define LOG_WARN(fmt, ...)  do {\
    const jcx::logger::Info info = {__FILE__, __LINE__, __func__}; \
    jcx::logger::LoggerProxy * logger = jcx::logger::LoggerProxy::instance(); \
    logger->varWarn(&info, fmt, ##__VA_ARGS__); \
    logger->flush();\
} while (0)

#define LOG_ERROR(fmt, ...)  do {\
    const jcx::logger::Info info = {__FILE__, __LINE__, __func__}; \
    jcx::logger::LoggerProxy * logger = jcx::logger::LoggerProxy::instance(); \
    logger->varError(&info, fmt, ##__VA_ARGS__); \
    logger->flush(); \
} while (0)


#define LOG_FLUSH()   do {\
    jcx::logger::LoggerProxy::instance()->flush(); \
} while (0)


#include <jcx/logger/Factory.h>

#define DECLARE_DEFAULT_LOGGER  jcx::logger::LoggerProxy::instance()->setFactory(0)
#define DECLARE_STDIN_LOGGER    jcx::logger::LoggerProxy::instance()->setFactory(new jcx::logger::StdoutFactory())
#define DECLARE_FILE_LOGGER(fn) jcx::logger::LoggerProxy::instance()->setFactory(new jcx::logger::FileLoggerFactory(fn))

#endif   /* LOGGER_H */
