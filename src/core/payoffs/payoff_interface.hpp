#pragma once
#include <string>
#include <vector>

#include "../enums/numerical_methods.hpp"
#include "../enums/model_method_pair.hpp"
#include "../enums/payoff_types.hpp"


namespace pricing {
    class Payoff {
    public:
        virtual ~Payoff() = default;

        virtual double calculate(double spot, double strike) const = 0;

        virtual bool isCompatible(PricingModel model, NumericalMethod method) const = 0;

        virtual PayoffType getType() const = 0;
        virtual std::string getName() const = 0;
        virtual bool canExerciseEarly() const = 0;
        virtual bool isPathDependent() const = 0;
        virtual double getStrike() const = 0;

        std::vector<ModelMethodPair> getCompatibleCombinations() const {
            std::vector<ModelMethodPair> compatible;
            std::vector<PricingModel> models = {
                PricingModel::BLACK_SCHOLES,
                PricingModel::BLACK_SCHOLES_MERTON,
                PricingModel::HESTON
            };

            std::vector<NumericalMethod> methods = {
                NumericalMethod::ANALYTICAL,
                NumericalMethod::MONTE_CARLO,
                NumericalMethod::BINOMIAL_TREE,
            };

            for (auto model : models) {
                for (auto method : methods) {
                    if (isCompatible(model, method)) {
                        compatible.push_back({model, method});
                    }
                }
            }

            return compatible;
        }
        virtual void updatePath(double spotPrice, double timeStep) {}
        virtual double getPathValue() const { return 0.0; }


    };
}
