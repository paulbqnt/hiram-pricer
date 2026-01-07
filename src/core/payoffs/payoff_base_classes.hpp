#pragma once
#include "payoff_interface.hpp"
#include "core/pricing/pricing_implementation.hpp"

namespace pricing {

class EuropeanPayoff : public Payoff {
public:
    bool canExerciseEarly() const override {
        return false;
    }

    bool isPathDependent() const override {
        return false;
    }

    // NEW API: Check compatibility with model + method combination
    bool isCompatible(PricingModel model, NumericalMethod method) const override {
        // European vanilla options work with analytical formulas for BS/BSM
        if ((model == PricingModel::BLACK_SCHOLES ||
             model == PricingModel::BLACK_SCHOLES_MERTON) &&
            method == NumericalMethod::ANALYTICAL) {
            return true;
        }

        // European options work with all numerical methods
        if (method == NumericalMethod::MONTE_CARLO ||
            method == NumericalMethod::BINOMIAL_TREE ||
            method == NumericalMethod::TRINOMIAL_TREE ||
            method == NumericalMethod::FINITE_DIFFERENCE) {
            return true;
        }

        return false;
    }
};



    class AmericanPayoff : public Payoff {
public:
    bool canExerciseEarly() const override {
        return true;
    }

    bool isPathDependent() const override {
        return false;
    }

    // American options CANNOT use analytical methods
    bool isCompatible(PricingModel model, NumericalMethod method) const override {
        // No closed-form solution exists for American options
        if (method == NumericalMethod::ANALYTICAL) {
            return false;
        }

        // Trees and finite difference work well
        if (method == NumericalMethod::BINOMIAL_TREE ||
            method == NumericalMethod::TRINOMIAL_TREE ||
            method == NumericalMethod::FINITE_DIFFERENCE) {
            return true;
        }

        // Monte Carlo requires Longstaff-Schwartz (LSM) - not implemented yet
        if (method == NumericalMethod::MONTE_CARLO) {
            return false; // TODO: Enable when LSM is implemented
        }

        return false;
    }

};


    class PathDependentPayoff : public Payoff {
public:
    bool canExerciseEarly() const override {
        return false;
    }

    bool isPathDependent() const override {
        return true;
    }

    // Path-dependent options need methods that can track the path
    bool isCompatible(PricingModel model, NumericalMethod method) const override {
        // No analytical solution for path-dependent (except geometric Asian)
        if (method == NumericalMethod::ANALYTICAL) {
            return false;
        }

        // Monte Carlo is the natural choice for path-dependent
        if (method == NumericalMethod::MONTE_CARLO) {
            return true;
        }

        // Trees become very complex (state explosion)
        // Finite difference needs extra state dimension
        // Not implemented yet
        if (method == NumericalMethod::BINOMIAL_TREE ||
            method == NumericalMethod::TRINOMIAL_TREE ||
            method == NumericalMethod::FINITE_DIFFERENCE) {
            return false; // TODO: Implement if needed
        }

        return false;
    }
};
}
