//
// Created by guillaume on 12/31/23.
//

#ifndef PLT_REQUESTHANDLER_H
#define PLT_REQUESTHANDLER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <state.h>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


class requestHandler {
public:
    static void log_command(http::request<http::string_body> &request,http::response<http::dynamic_body> &response);
    static void create_response(http::request<http::string_body> &request,http::response<http::dynamic_body> &response);
    static  void process_request(http::request<http::string_body> &request,http::response<http::dynamic_body> &response);
private:
    static state::GameState generateSampleState();
};


#endif //PLT_REQUESTHANDLER_H
