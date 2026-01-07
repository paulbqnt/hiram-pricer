#pragma once

#include "payoff_base_classes.hpp"
#include <algorithm>
#include <cmath>


namespace pricing {

    class EuropeanVanillaCall : public EuropeanPayoff {
        private:
            double strike_;
        public:
            explicit EuropeanVanillaCall(double strike): strike_(strike) {}

            double calculate(double spot, double strike) const override {
                return std::max(spot - strike, 0.0);
            }

     bool isCompatible(PricingModel model, NumericalMethod method) const override {
            // Same as call
            if ((model == PricingModel::BLACK_SCHOLES ||
                 model == PricingModel::BLACK_SCHOLES_MERTON) &&
                method == NumericalMethod::ANALYTICAL) {
                return true;
            }

            if (method == NumericalMethod::MONTE_CARLO ||
                method == NumericalMethod::BINOMIAL_TREE ||
                method == NumericalMethod::TRINOMIAL_TREE ||
                method == NumericalMethod::FINITE_DIFFERENCE) {
                return true;
            }

            return false;
        }
            PayoffType getType() const override { return PayoffType::EUROPEAN_VANILLA_CALL; }
            std::string getName() const override { return "European Vanilla Call"; }
            bool canExerciseEarly() const override { return false; }
            bool isPathDependent() const override { return false; }
            double getStrike() const override { return strike_; }
    };

}