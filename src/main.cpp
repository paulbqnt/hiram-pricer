#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void handle_session(tcp::socket socket) {
    try {
        beast::flat_buffer buffer;

        http::request<http::string_body> request;
        http::read(socket, buffer, request);

        std::cout << "Received request: " << request.method_string() << " " << request.target() << std::endl;

        http::response<http::string_body> response{
            http::status::ok, request.version()};
        response.set(http::field::server, "Boost.Beast");
        response.set(http::field::content_type, "text/plain");
        response.body() = "Hello, World from Boost.Beast!";
        response.prepare_payload();

        http::write(socket, response);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}



int main() {
    std::cout << "Hello, World!" << std::endl;
    try {
        const auto address = net::ip::make_address("0.0.0.0");
        const unsigned short port = 8080;

        net::io_context ioc;

        tcp::acceptor acceptor{ioc, {address, port}};

        for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            handle_session(std::move(socket));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}