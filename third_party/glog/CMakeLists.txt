add_library(ThirdParty.glog STATIC)
add_library(ThirdParty::glog ALIAS ThirdParty.glog)

target_precompile_headers(ThirdParty.glog PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include/glog/logging.h
)

target_sources(ThirdParty.glog PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/base/commandlineflags.h
  ${CMAKE_CURRENT_LIST_DIR}/src/base/googleinit.h
  ${CMAKE_CURRENT_LIST_DIR}/src/base/mutex.h
  ${CMAKE_CURRENT_LIST_DIR}/src/demangle.cc
  ${CMAKE_CURRENT_LIST_DIR}/src/demangle.h
  ${CMAKE_CURRENT_LIST_DIR}/src/logging.cc
  ${CMAKE_CURRENT_LIST_DIR}/src/raw_logging.cc
  ${CMAKE_CURRENT_LIST_DIR}/src/symbolize.cc
  ${CMAKE_CURRENT_LIST_DIR}/src/symbolize.h
  ${CMAKE_CURRENT_LIST_DIR}/src/utilities.cc
  ${CMAKE_CURRENT_LIST_DIR}/src/utilities.h
  ${CMAKE_CURRENT_LIST_DIR}/src/vlog_is_on.cc
  ${CMAKE_CURRENT_LIST_DIR}/src/signalhandler.cc
)

target_include_directories(ThirdParty.glog
  SYSTEM PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(ThirdParty.glog
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/glog
)

target_compile_options(ThirdParty.glog PRIVATE -w)

find_package(Threads REQUIRED)
target_link_libraries(ThirdParty.glog PUBLIC Threads::Threads)
