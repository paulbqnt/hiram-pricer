#pragma once
#include "pricing_implementation.hpp"
#include "pricing_result.hpp"
#include "../enums/pricing_models.hpp"
#include "../enums/numerical_methods.hpp"
#include "../enums/model_method_pair.hpp"
#include "../market_data/market_data.hpp"
#include <functional>
#include <unordered_map>

namespace pricing {

    class PricingEngine {
public:
    PricingEngine();

    // PRIMARY API: Type-safe with separate model and method
    PricingResult price(
        const Option& option,
        const MarketData& marketData,
        PricingModel model,
        NumericalMethod method
    ) const;

    // SECONDARY API: String-based (for JSON/HTTP)
    PricingResult price(
        const Option& option,
        const MarketData& marketData,
        const std::string& modelName,
        const std::string& methodName
    ) const;

    // Query compatibility
    std::vector<ModelMethodPair> getCompatibleCombinations(
        const Option& option
    ) const;

    bool isCompatible(
        const Option& option,
        PricingModel model,
        NumericalMethod method
    ) const;

    std::vector<ModelMethodPair> getAllRegisteredCombinations() const;

    // Registration
    void registerImplementation(
        PricingModel model,
        NumericalMethod method,
        std::function<std::unique_ptr<PricingImplementation>()> creator
    );

private:
    std::unordered_map<
        ModelMethodPair,
        std::function<std::unique_ptr<PricingImplementation>()>,
        ModelMethodPairHash
    > implementations_;

    void registerDefaultImplementations();
};
}