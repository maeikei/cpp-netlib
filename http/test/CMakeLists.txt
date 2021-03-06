# Copyright 2010 Dean Michael Berris.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(
  ${CPP-NETLIB_SOURCE_DIR}/uri/src
  ${CPP-NETLIB_SOURCE_DIR}/message/src
  ${CPP-NETLIB_SOURCE_DIR}/logging/src
  ${CPP-NETLIB_SOURCE_DIR}/http/src
  ${GTEST_INCLUDE_DIRS}
  ${CPP-NETLIB_SOURCE_DIR})

if (OPENSSL_FOUND)
    include_directories( ${OPENSSL_INCLUDE_DIR} )
    add_definitions(-DNETWORK_ENABLE_HTTPS)
endif()

if( NOT CPP-NETLIB_DISABLE_LOGGING )
  set( CPP-NETLIB_LOGGING_LIB cppnetlib-logging )
endif()

  # this library name is defined only if we created the target
  # if not then it will be empty
  set( CPP-NETLIB_LOGGING_LIB cppnetlib-logging )

if (CPP-NETLIB_BUILD_TESTS)
    # These are the internal (simple) tests.
    set (MESSAGE_TESTS
        request_base_test
        request_test
        response_test
        response_incremental_parser_test)
    if(CPP-NETLIB_BUILD_SINGLE_LIB)
      set(link_cppnetlib_lib cppnetlib)
      set(dependencies cppnetlib)
    else()
      set(link_cppnetlib_lib cppnetlib-message
            cppnetlib-message-wrappers
            cppnetlib-http-message
            cppnetlib-http-message-wrappers
            cppnetlib-uri
            cppnetlib-constants)
      set(dependencies cppnetlib-message
            cppnetlib-message-wrappers
            cppnetlib-http-message
            cppnetlib-http-message-wrappers
            cppnetlib-uri
            cppnetlib-constants)
    endif()
    foreach ( test ${MESSAGE_TESTS} )
        if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
            set_source_files_properties(${test}.cpp
                PROPERTIES COMPILE_FLAGS "-Wall")
        endif()
        add_executable(cpp-netlib-http-${test} ${test}.cpp)
        add_dependencies(cpp-netlib-http-${test} ${dependencies})
        target_link_libraries(cpp-netlib-http-${test}
            ${Boost_LIBRARIES}
            ${GTEST_BOTH_LIBRARIES}
            ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT}
            ${link_cppnetlib_lib})
        set_target_properties(cpp-netlib-http-${test}
            PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
        add_test(cpp-netlib-http-${test}
            ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-${test})
    endforeach(test)

    if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
        set_source_files_properties(client_test.cpp
            PROPERTIES COMPILE_FLAGS "-Wall")
    endif()
    if(CPP-NETLIB_BUILD_SINGLE_LIB)
      set(link_cppnetlib_lib cppnetlib)
    else()
      set(link_cppnetlib_lib cppnetlib-constants
        cppnetlib-uri
        cppnetlib-message
        cppnetlib-message-wrappers
        cppnetlib-message-directives
        ${CPP-NETLIB_LOGGING_LIB}
        cppnetlib-http-message
        cppnetlib-http-message-wrappers
        cppnetlib-http-client
        cppnetlib-http-client-connections
        cppnetlib-logging)
    endif()
    add_executable(cpp-netlib-http-client_test client_test.cpp)
    target_link_libraries(cpp-netlib-http-client_test
        ${Boost_LIBRARIES}
        ${GTEST_BOTH_LIBRARIES}
        ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${link_cppnetlib_lib})
    if (OPENSSL_FOUND)
        target_link_libraries(cpp-netlib-http-client_test ${OPENSSL_LIBRARIES})
    endif()
    set_target_properties(cpp-netlib-http-client_test
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
    add_test(cpp-netlib-http-client_test
        ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-client_test)

#    set ( SERVER_API_TESTS
#        server_constructor_test
#        server_async_run_stop_concurrency
#        )
#    foreach ( test ${SERVER_API_TESTS} )
#        if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
#            set_source_files_properties(${test}.cpp
#                PROPERTIES COMPILE_FLAGS "-Wall")
#        endif()
#        add_executable(cpp-netlib-http-${test} ${test}.cpp)
#        target_link_libraries(cpp-netlib-http-${test}
#            ${Boost_LIBRARIES}
#            ${GTEST_BOTH_LIBRARIES}
#            ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
#            ${CMAKE_THREAD_LIBS_INIT}
#            cppnetlib-constants
#            cppnetlib-uri
#            cppnetlib-message
#            cppnetlib-message-wrappers
#            cppnetlib-http-message
#            cppnetlib-http-server
#            cppnetlib-http-server-parsers
#            cppnetlib-utils-thread_pool
#            )
#        set_target_properties(cpp-netlib-http-${test}
#            PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
#        add_test(cpp-netlib-http-${test}
#            ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-${test})
#    endforeach (test)

endif()
