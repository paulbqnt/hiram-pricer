#pragma once
#include <cmath>

#include "../../pricing/pricing_implementation.hpp"

class BlackScholesAnalytical : public pricing::PricingImplementation {
public:
    BlackScholesAnalytical() = default;

    pricing::PricingResult price(const pricing::Option& option, const pricing::MarketData& marketData) override;
    std::string getName() const override { return "Black-Scholes"; }

private:
    double calculateCallPrice(double S, double K, double T, double r, double sigma) const;
    double calculatePutPrice(double S, double K, double T, double r, double sigma) const;

    double normalCDF(double x) const;
    double calculateD1(double S, double K, double T, double r, double sigma) const;
    double calculateD2(double S, double K, double T, double r, double sigma) const;
};