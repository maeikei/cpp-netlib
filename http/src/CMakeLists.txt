# Copyright (c) Glyn Matthews 2011, 2012.
# Copyright 2011 Dean Michael Berris (dberris@google.com)
# Copyright 2012 A. Joel Lamotte (mjklaim@gmail.com)
# Copyright 2011 Google, Inc.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


include_directories(
  ${CPP-NETLIB_SOURCE_DIR}/uri/src
  ${CPP-NETLIB_SOURCE_DIR}/message/src
  ${CPP-NETLIB_SOURCE_DIR}/logging/src
  ${CPP-NETLIB_SOURCE_DIR}/http/src
  ${CPP-NETLIB_SOURCE_DIR})

if (OPENSSL_FOUND)
include_directories(${OPENSSL_INCLUDE_DIR})
endif()

if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  if (HAVE_STD11)
    set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11")
  elseif (HAVE_STD0X)
    set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++0x")
  endif()
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)
  if (CPP-NETLIB_DISABLE_LIBCXX)
    set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11")
  else()
    set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11 -stdlib=libc++")
  endif()
endif()

set(CPP-NETLIB_HTTP_MESSAGE_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/http/request.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/http/response.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-http-message ${CPP-NETLIB_HTTP_MESSAGE_SRCS})
  add_dependencies(cppnetlib-http-message
#     ${Boost_LIBRARIES}
    cppnetlib-message)
  target_link_libraries(cppnetlib-http-message
    ${Boost_LIBRARIES}
    cppnetlib-message)
  install(
    TARGETS
    cppnetlib-http-message
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )

endif()
foreach (src_file ${CPP-NETLIB_HTTP_MESSAGE_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/http/message/wrappers.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-http-message-wrappers ${CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS})
  install(
    TARGETS
    cppnetlib-http-message-wrappers
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )
endif()
foreach (src_file ${CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)


set(CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/http/client_connections.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/simple_connection_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/simple_connection_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/connection_delegate_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/client_resolver_delegate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/client_resolver_delegate_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/client_connection_delegates.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/client_connection_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/client_async_resolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/http/client_connection_normal.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-http-client-connections ${CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS})
  install(
    TARGETS
    cppnetlib-http-client-connections
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )
endif()
foreach (src_file ${CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_HTTP_CLIENT_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/http/client.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-http-client ${CPP-NETLIB_HTTP_CLIENT_SRCS})
  add_dependencies(cppnetlib-http-client
    ${CPP-NETLIB_LOGGING_LIB}
    cppnetlib-constants
    cppnetlib-uri
    cppnetlib-message
    cppnetlib-message-wrappers
    cppnetlib-message-directives
    cppnetlib-http-message
    cppnetlib-http-message-wrappers
    cppnetlib-http-client-connections
    )
  target_link_libraries(cppnetlib-http-client
    ${Boost_LIBRARIES}
    ${CPP-NETLIB_LOGGING_LIB}
    cppnetlib-constants
    cppnetlib-uri
    cppnetlib-message
    cppnetlib-message-wrappers
    cppnetlib-message-directives
    cppnetlib-http-message
    cppnetlib-http-message-wrappers
    cppnetlib-http-client-connections
    )
  install(
    TARGETS
    cppnetlib-http-client
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )

endif()
foreach (src_file ${CPP-NETLIB_HTTP_CLIENT_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_CONSTANTS_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/constants.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-constants ${CPP-NETLIB_CONSTANTS_SRCS})
  install(
    TARGETS
    cppnetlib-constants
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )

endif()
foreach (src_file ${CPP-NETLIB_CONSTANTS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)


# propagate sources to parent directory for one-lib-build
set(CPP-NETLIB_HTTP_MESSAGE_SRCS ${CPP-NETLIB_HTTP_MESSAGE_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS ${CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS ${CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_HTTP_CLIENT_SRCS ${CPP-NETLIB_HTTP_CLIENT_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_CONSTANTS_SRCS ${CPP-NETLIB_CONSTANTS_SRCS} PARENT_SCOPE)


install(DIRECTORY network
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

