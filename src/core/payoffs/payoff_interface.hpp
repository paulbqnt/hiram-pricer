#pragma once
#include <string>
#include <vector>

#include "../enums/model_types.hpp"
#include "../enums/payoff_types.hpp"

namespace pricing {
    class Payoff {
    public:
        virtual ~Payoff() = default;

        virtual double calculate(double spot, double strike) const = 0;
        virtual bool acceptModel(ModelType model) const = 0;

        virtual PayoffType getType() const = 0;
        virtual std::string getName() const = 0;
        virtual bool canExerciseEarly() const = 0;
        virtual bool isPathDependent() const = 0;

        virtual void updatePath(double spotPrice, double timeStep) {}
        virtual double getPathValue() const { return 0.0; }
        virtual double getStrike() const = 0;

        std::vector<ModelType> getCompatibleModels() const {
            std::vector<ModelType> compatible;

            std::vector<ModelType> allModels = {
                ModelType::BLACK_SCHOLES,
                ModelType::BLACK_SCHOLES_MERTON,
                ModelType::BINOMIAL_TREE,
                ModelType::MONTE_CARLO
            };

            for (ModelType model : allModels) {
                if (acceptModel(model)) {
                    compatible.push_back(model);
                }
            }

            return compatible;
        }
    };
}
