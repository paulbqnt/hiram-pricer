#include "../../market_data/market_data.hpp"
#include "black_scholes.hpp"
#include "../../instruments/base/option.hpp"
#include "../../pricing/pricing_result.hpp"
#include <cmath>
#include <stdexcept>

pricing::PricingResult BlackScholesModel::price(const pricing::Option& option, const pricing::MarketData& marketData) {
    try {
        double S = marketData.getSpotPrice();
        double K = option.getStrike();
        double T = option.getTimeToExpiry();
        double r = marketData.getRiskFreeRate();
        double sigma = marketData.getVolatility();

        if (S <= 0 || K <= 0 || T <= 0 || sigma <= 0) {
            return pricing::PricingResult("Invalid parameters: all values must be positive", getName());
        }

        // *** FIXED: Actually calculate the price based on payoff type ***
        double price = 0.0;

        // Check payoff type and calculate accordingly
        auto payoffType = option.getPayoff().getType();

        if (payoffType == pricing::PayoffType::EUROPEAN_VANILLA_CALL) {
            price = calculateCallPrice(S, K, T, r, sigma);
        } else if (payoffType == pricing::PayoffType::EUROPEAN_VANILLA_PUT) {
            price = calculatePutPrice(S, K, T, r, sigma);
        } else {
            return pricing::PricingResult("Unsupported payoff type for Black-Scholes", getName());
        }

        return pricing::PricingResult(price, getName());

    } catch (const std::exception& e) {
        return pricing::PricingResult(std::string("Black-Scholes calculation error: ") + e.what(), getName());
    }
}

double BlackScholesModel::calculateCallPrice(double S, double K, double T, double r, double sigma) const {
    double d1 = calculateD1(S, K, T, r, sigma);
    double d2 = calculateD2(S, K, T, r, sigma);
    return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
}

// *** FIXED: This was completely wrong ***
double BlackScholesModel::calculatePutPrice(double S, double K, double T, double r, double sigma) const {
    double d1 = calculateD1(S, K, T, r, sigma);
    double d2 = calculateD2(S, K, T, r, sigma);
    return K * std::exp(-r * T) * normalCDF(-d2) - S * normalCDF(-d1);
}

double BlackScholesModel::normalCDF(double x) const {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

double BlackScholesModel::calculateD1(double S, double K, double T, double r, double sigma) const {
    return (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
}

double BlackScholesModel::calculateD2(double S, double K, double T, double r, double sigma) const {
    return calculateD1(S, K, T, r, sigma) - sigma * std::sqrt(T);
}