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


    const pricing::PricingEngine engine;
    pricing::MarketData market(100.0, 0.20, 0.05);

    auto euroCall = std::make_unique<pricing::EuropeanVanillaCall>(110.0);
    pricing::Option callOption(std::move(euroCall), 1.0);

    auto start = std::chrono::high_resolution_clock::now();

    auto result = engine.price(
        callOption,
        market,
        pricing::PricingModel::BLACK_SCHOLES,
        pricing::NumericalMethod::ANALYTICAL);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Pricing took: " << duration.count() << " ns\n";

    if (!result.hasError()) {
        std::cout << "\nEuropean Call Price: $" << result.getPrice() << std::endl;
        std::cout << "Method: " << result.toString() << std::endl;
    } else {
        std::cout << "\nError: " << result.getErrorMessage() << std::endl;
    }

    // 2. Query compatible combinations
    std::cout << "\nCompatible pricing methods:" << std::endl;
    auto compatible = engine.getCompatibleCombinations(callOption);
    for (const auto& pair : compatible) {
        std::cout << "  - " << pricing::toString(pair) << std::endl;
    }

    return 0;
}
