#pragma once

#include "payoff_base_classes.hpp"
#include <algorithm>
#include <cmath>


namespace pricing {
    class EuropeanVanillaCall : public EuropeanPayoff {
    public:
        explicit EuropeanVanillaCall(double strike): strike_(strike) {}

        double calculate(double spot, double strike) const override {
            return std::max(spot - strike, 0.0);
        }

        PayoffType getType() const override { return PayoffType::EUROPEAN_VANILLA_CALL; }
        std::string getName() const override { return "European Vanilla Call"; }
        double getStrike() const { return strike_; }
    private:
        double strike_;
    };
}