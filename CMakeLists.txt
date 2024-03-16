#-------------------------------------------------------------------------------
# Project basic configurations
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
  message(WARNING "CMAKE_BUILD_TYPE not give, set to Debug")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -Wreturn-type -Wno-unused-function -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wreturn-type -Wno-unused-function -Werror")
# set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -Wall -Wextra -Weffc++ -pedantic")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)


#-------------------------------------------------------------------------------
# Add project library
#-------------------------------------------------------------------------------
project(my_test)
add_executable(${PROJECT_NAME})
#src file
target_sources(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src/fmt_test.cpp
)

#test file
target_sources(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/test/test.cpp
)


target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
)


# fmtlib
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/fmt)
target_link_libraries(${PROJECT_NAME} PUBLIC ThirdParty::fmt)


# target_link_libraries(${PROJECT_NAME} PUBLIC ThirdParty::fmt)