#ifndef UTILS_LOG_HPP
#define UTILS_LOG_HPP

#include <atomic>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <glog/logging.h>

#define CALMCAR_PP_CAT_I(a, b) a##b
#define CALMCAR_PP_CAT(a, b) CALMCAR_PP_CAT_I(a, b)

#define _CALMCAR_LOG_IS_ON(severity) \
  (FLAGS_minloglevel <= google::GLOG_##severity)

#define _CALMCAR_LOG_IF(condition, logger, format_string, ...)          \
  do                                                                    \
    for (bool __calmcar_log_b = true; __calmcar_log_b && !!(condition); \
         __calmcar_log_b = false) {                                     \
      logger << __FUNCTION__ << "()	"                                   \
             << fmt::format(format_string, ##__VA_ARGS__);              \
    }                                                                   \
  while (0)

#define _CALMCAR_LOG_IF_EVERY_N(condition, n, logger, format_string, ...)      \
  do {                                                                         \
    static std::atomic_bool CALMCAR_PP_CAT(_calmcar_log_if_flag, __LINE__) =   \
        ATOMIC_VAR_INIT(!!(condition));                                        \
    static std::atomic_int CALMCAR_PP_CAT(_calmcar_log_if_counter, __LINE__) = \
        ATOMIC_VAR_INIT(0);                                                    \
    static int CALMCAR_PP_CAT(_calmcar_log_if_every_n, __LINE__) = (n);        \
    for (bool __calmcar_log_b = true;                                          \
         __calmcar_log_b && CALMCAR_PP_CAT(_calmcar_log_if_flag, __LINE__) &&  \
         (CALMCAR_PP_CAT(_calmcar_log_if_counter, __LINE__).fetch_add(1) ==    \
          CALMCAR_PP_CAT(_calmcar_log_if_every_n, __LINE__));                  \
         __calmcar_log_b = false)                                              \
      logger << __FUNCTION__ << "()	"                                          \
             << fmt::format(format_string, ##__VA_ARGS__);                     \
  } while (0)

#ifndef ENABLE_DLT

#define _CALMCAR_LOGGER(severity) LOG(severity)

#else  // ENABLE_DLT

google::LogSink* _calmcar_dlt_log_sink_instance();

#define _CALMCAR_LOGGER(severity) \
  LOG_TO_SINK_BUT_NOT_TO_LOGFILE(_calmcar_dlt_log_sink_instance(), severity)

#endif  // ENABLE_DLT




/** All log content of `format_string, ...` are formatted with `fmt::format`.
 *  Cheat-sheets: https://hackingcpp.com/cpp/libs/fmt.html#cheat-sheets */

/** Used by CALMCAR_TRACE(verboselevel=100) and CALMCAR_DEBUG(verboselevel=50),
 *  could be invked manually for other verbose level */
#define CALMCAR_VLOG(verboselevel, format_string, ...)                  \
  _CALMCAR_LOG_IF(VLOG_IS_ON(verboselevel) && _CALMCAR_LOG_IS_ON(INFO), \
                  _CALMCAR_LOGGER(INFO), format_string, ##__VA_ARGS__)
/** Check format at compile time,
 *  require format_string is a string literal instead of std::string */
#define CALMCAR_VLOG_S(verboselevel, format_string, ...) \
  CALMCAR_VLOG(verboselevel, FMT_STRING(format_string), ##__VA_ARGS__)

// Used by CALMCAR_XXX with level >= INFO
#define CALMCAR_LOG(severity, format_string, ...)                          \
  _CALMCAR_LOG_IF(_CALMCAR_LOG_IS_ON(severity), _CALMCAR_LOGGER(severity), \
                  format_string, ##__VA_ARGS__)
/** Check format at compile time,
 *  require format_string is a string literal instead of std::string */
#define CALMCAR_LOG_S(severity, format_string, ...) \
  CALMCAR_LOG(severity, FMT_STRING(format_string), ##__VA_ARGS__)

#define CALMCAR_LOG_EVERY_N(severity, n, format_string, ...)        \
  _CALMCAR_LOG_IF_EVERY_N(_CALMCAR_LOG_IS_ON(severity), n,          \
                          _CALMCAR_LOGGER(severity), format_string, \
                          ##__VA_ARGS__)
#define CALMCAR_LOG_EVERY_N_S(severity, n, format_string, ...) \
  CALMCAR_LOG_EVERY_N(severity, n, FMT_STRING(format_string), ##__VA_ARGS__)

// format_string cound be string literal or std::string
#define CALMCAR_TRACE(format_string, ...) \
  CALMCAR_VLOG(100, format_string, ##__VA_ARGS__)
/** Check format at compile time,
 *  require format_string is a string literal instead of std::string */
#define CALMCAR_TRACE_S(format_string, ...) \
  CALMCAR_TRACE(FMT_STRING(format_string), ##__VA_ARGS__)

// format_string cound be string literal or std::string
#define CALMCAR_DEBUG(format_string, ...) \
  CALMCAR_VLOG(50, format_string, ##__VA_ARGS__)
/** Check format at compile time,
 *  require format_string is a string literal instead of std::string */
#define CALMCAR_DEBUG_S(format_string, ...) \
  CALMCAR_DEBUG(FMT_STRING(format_string), ##__VA_ARGS__)

// format_string cound be string literal or std::string
#define CALMCAR_INFO(format_string, ...) \
  CALMCAR_LOG(INFO, format_string, ##__VA_ARGS__)
/** Check format at compile time,
 *  require format_string is a string literal instead of std::string */
#define CALMCAR_INFO_S(format_string, ...) \
  CALMCAR_INFO(FMT_STRING(format_string), ##__VA_ARGS__)

// format_string cound be string literal or std::string
#define CALMCAR_WARN(format_string, ...) \
  CALMCAR_LOG(WARNING, format_string, ##__VA_ARGS__)
/** Check format at compile time,
 *  require format_string is a string literal instead of std::string */
#define CALMCAR_WARN_S(format_string, ...) \
  CALMCAR_WARN(FMT_STRING(format_string), ##__VA_ARGS__)

// format_string cound be string literal or std::string
#define CALMCAR_ERROR(format_string, ...) \
  CALMCAR_LOG(ERROR, format_string, ##__VA_ARGS__)
/** Check format at compile time,
 *  require format_string is a string literal instead of std::string */
#define CALMCAR_ERROR_S(format_string, ...) \
  CALMCAR_ERROR(FMT_STRING(format_string), ##__VA_ARGS__)

// format_string cound be string literal or std::string
#define CALMCAR_CRIT(format_string, ...) \
  CALMCAR_LOG(FATAL, format_string, ##__VA_ARGS__)
/** Check format at compile time,
 *  require format_string is a string literal instead of std::string */
#define CALMCAR_CRIT_S(format_string, ...) \
  CALMCAR_CRIT(FMT_STRING(format_string), ##__VA_ARGS__)


#endif