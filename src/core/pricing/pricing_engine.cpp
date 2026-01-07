#include "pricing_engine.hpp"
#include "../instruments/base/option.hpp"
#include "../models/analytical/black_scholes_analytical.hpp"
#include <vector>
#include <functional>
#include <stdexcept>

namespace pricing {
    // *** PRIMARY METHOD: ModelType enum ***
    PricingEngine::PricingEngine() {
        registerDefaultImplementations();
    }

    PricingResult PricingEngine::price(
        const Option& option,
        const MarketData& marketData,
        PricingModel model,
        NumericalMethod method
    ) const {
        // Check compatibility
        if (!option.getPayoff().isCompatible(model, method)) {
            auto compatible = getCompatibleCombinations(option);

            std::string error = "Cannot price " + option.getPayoff().getName() +
                              " with " + toString(model) + " + " + toString(method);

            if (!compatible.empty()) {
                error += "\n\nCompatible combinations:";
                for (const auto& pair : compatible) {
                    error += "\n  - " + toString(pair);
                }
            } else {
                error += "\n\nNo compatible combinations available.";
            }

            return PricingResult(error, toString(model) + "+" + toString(method));
        }

        // Find implementation
        ModelMethodPair key{model, method};
        auto it = implementations_.find(key);

        if (it == implementations_.end()) {
            return PricingResult(
                "No implementation registered for " + toString(key),
                toString(key)
            );
        }

        // Create and execute
        try {
            auto implementation = it->second();
            return implementation->price(option, marketData);
        } catch (const std::exception& e) {
            return PricingResult(
                std::string("Pricing error: ") + e.what(),
                toString(key)
            );
        }
    }

    PricingResult PricingEngine::price(
        const Option& option,
        const MarketData& marketData,
        const std::string& modelName,
        const std::string& methodName
    ) const {
        try {
            PricingModel model = stringToPricingModel(modelName);
            NumericalMethod method = stringToNumericalMethod(methodName);
            return price(option, marketData, model, method);
        } catch (const std::exception& e) {
            return PricingResult(
                std::string("Invalid model/method: ") + e.what(),
                modelName + "+" + methodName
            );
        }
    }

    std::vector<ModelMethodPair> PricingEngine::getCompatibleCombinations(
        const Option& option
    ) const {
        return option.getPayoff().getCompatibleCombinations();
    }

    bool PricingEngine::isCompatible(
        const Option& option,
        PricingModel model,
        NumericalMethod method
    ) const {
        return option.getPayoff().isCompatible(model, method);
    }

    std::vector<ModelMethodPair> PricingEngine::getAllRegisteredCombinations() const {
        std::vector<ModelMethodPair> combinations;
        combinations.reserve(implementations_.size());

        for (const auto& [pair, creator] : implementations_) {
            combinations.push_back(pair);
        }

        return combinations;
    }

    void PricingEngine::registerImplementation(
        PricingModel model,
        NumericalMethod method,
        std::function<std::unique_ptr<PricingImplementation>()> creator
    ) {
        implementations_[{model, method}] = std::move(creator);
    }

    void PricingEngine::registerDefaultImplementations() {
        // Black-Scholes + Analytical
        registerImplementation(
            PricingModel::BLACK_SCHOLES,
            NumericalMethod::ANALYTICAL,
            []() { return std::make_unique<BlackScholesAnalytical>(); }
        );
    }
}
