#include "log.hpp"

#ifdef ENABLE_DLT

#include <dlt_sink/dlt_log_sink.h>

google::LogSink* _calmcar_dlt_log_sink_instance() {
  return &DLTLogSink::instance();
}

#endif  // ENABLE_DLT
