// Copyright 2012 Dean Michael Berris <dberris@google.com>.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_PROTOCOL_HTTP_SERVER_IMPL_HPP_20120318
#define NETWORK_PROTOCOL_HTTP_SERVER_IMPL_HPP_20120318

#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <boost/asio/ip/tcp.hpp>
#include <network/protocol/http/server/impl/socket_options_setter.hpp>
#include <network/protocol/http/server/options.hpp>
#include <functional>

namespace network {
namespace http {

class sync_server_connection;
struct request;
struct response;

class sync_server_impl : protected socket_options_setter {
 public:
  sync_server_impl(server_options const& options,
                   std::function<void(request const&, response&)> handler);
  void run();
  void stop();
  void listen();

 private:
  server_options options_;
  std::string address_, port_;
  boost::asio::io_service* service_;
  boost::asio::ip::tcp::acceptor* acceptor_;
  std::shared_ptr<sync_server_connection> new_connection_;
  std::mutex listening_mutex_;
  bool listening_, owned_service_;
  std::function<void(request const&, response&)> handler_;

  void start_listening();
  void handle_accept(boost::system::error_code const& ec);
};

}       // namespace http
}       // namespace network
#endif  // NETWORK_PROTOCOL_HTTP_SERVER_IMPL_HPP_20120318
