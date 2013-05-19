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

include_directories(${CPP-NETLIB_SOURCE_DIR}/uri/src ${CPP-NETLIB_SOURCE_DIR}/message/src)

set(CPP-NETLIB_MESSAGE_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/message.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-message ${CPP-NETLIB_MESSAGE_SRCS})
  add_dependencies(cppnetlib-message cppnetlib-uri)
  target_link_libraries(cppnetlib-message cppnetlib-uri)
  install(
    TARGETS
    cppnetlib-message
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )

endif()
foreach (src_file ${CPP-NETLIB_MESSAGE_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/directives.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-message-directives ${CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS})
endif()
foreach (src_file ${CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_MESSAGE_WRAPPERS_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/wrappers.cpp)
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  add_library(cppnetlib-message-wrappers ${CPP-NETLIB_MESSAGE_WRAPPERS_SRCS})
endif()
foreach (src_file ${CPP-NETLIB_MESSAGE_WRAPPERS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

# propagate sources to parent directory for one-lib-build
set(CPP-NETLIB_MESSAGE_SRCS ${CPP-NETLIB_MESSAGE_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS ${CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_MESSAGE_WRAPPERS_SRCS ${CPP-NETLIB_MESSAGE_WRAPPERS_SRCS} PARENT_SCOPE)

install(DIRECTORY network
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

