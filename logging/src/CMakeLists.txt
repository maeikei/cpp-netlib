# Copyright (c) Glyn Matthews 2012.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)
  if (CPP-NETLIB_DISABLE_LIBCXX)
    set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11")
  else()
    set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11 -stdlib=libc++")
  endif()
endif()

include_directories(${CPP-NETLIB_SOURCE_DIR}/logging/src)
set(CPP-NETLIB_LOGGING_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/logging.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-logging ${CPP-NETLIB_LOGGING_SRCS})
  install(
    TARGETS
    cppnetlib-logging
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )
endif()
foreach (src_file ${CPP-NETLIB_LOGGING_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

# propagate sources to parent directory for one-lib-build
set(CPP-NETLIB_LOGGING_SRCS ${CPP-NETLIB_LOGGING_SRCS} PARENT_SCOPE)

install(DIRECTORY network
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)
