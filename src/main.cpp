#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "core/instruments/base/option.hpp"
#include "core/payoffs/concrete_payoffs.hpp"
#include "core/pricing/pricing_engine.hpp"

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
            http::status::ok, request.version()
        };
        response.set(http::field::server, "Boost.Beast");
        response.set(http::field::content_type, "text/plain");
        response.body() = "Hello, World from Boost.Beast!";
        response.prepare_payload();

        http::write(socket, response);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}


int main() {
    // TODO: add fixing, payment date and direction
    // TODO: think about a way to handle greeks
    pricing::PricingEngine engine;
    pricing::MarketData market(100.0, 0.20, 0.2);
    std::cout << "Hello" << std::endl;
    //
    // auto euroCall = std::make_unique<pricing::EuropeanVanillaCall>(110.0);
    // pricing::Option option(std::move(euroCall), 1.0);
    //
    // auto result = engine.price(option, market, pricing::ModelType::BLACK_SCHOLES);
    // std::cout << result.getPrice() << std::endl;

    return 0;
    // std::cout << "Hello, World!" << std::endl;
    // try {
    //     const auto address = net::ip::make_address("0.0.0.0");
    //     const unsigned short port = 8080;
    //
    //     net::io_context ioc;
    //
    //     tcp::acceptor acceptor{ioc, {address, port}};
    //
    //     for (;;) {
    //         tcp::socket socket{ioc};
    //         acceptor.accept(socket);
    //         handle_session(std::move(socket));
    //     }
    // } catch (const std::exception &e) {
    //     std::cerr << "Error: " << e.what() << "\n";
    //     return EXIT_FAILURE;
    // }
}
