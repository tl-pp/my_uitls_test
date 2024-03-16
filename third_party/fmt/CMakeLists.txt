add_library(ThirdParty.fmt STATIC)
add_library(ThirdParty::fmt ALIAS ThirdParty.fmt)

target_precompile_headers(ThirdParty.fmt PUBLIC
  "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_LIST_DIR}/include/fmt/format.h>"
)

target_sources(ThirdParty.fmt PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/format.cc
  ${CMAKE_CURRENT_LIST_DIR}/src/os.cc
)

target_include_directories(ThirdParty.fmt
  SYSTEM PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_options(ThirdParty.fmt PRIVATE -w)

find_package(Threads REQUIRED)
target_link_libraries(ThirdParty.fmt PUBLIC Threads::Threads)
