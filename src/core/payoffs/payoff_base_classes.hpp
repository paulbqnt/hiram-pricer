#pragma once
#include "payoff_interface.hpp"

namespace pricing {
    class EuropeanPayoff : public Payoff {
    public:
        bool canExerciseEarly() const override { return false; }
        bool isPathDependent() const override { return false; }

        bool acceptModel(ModelType model) const override {
            switch (model) {
                case ModelType::BLACK_SCHOLES:
                    return true;
                default:
                    return false;
            }

        };
    };
}