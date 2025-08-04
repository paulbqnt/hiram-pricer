#pragma once
#include "pricing_model.hpp"
#include "pricing_result.hpp"
#include "../enums/model_types.hpp"
#include "../market_data/market_data.hpp"
#include <functional>
#include <unordered_map>

namespace pricing {

    class PricingEngine {
    public:
        PricingEngine();

        // *** PRIMARY API: ModelType enum (type-safe) ***
        PricingResult price(
            const Option& option,
            const MarketData& marketData,
            ModelType modelType) const;

        // *** SECONDARY API: String (JSON compatibility) ***
        PricingResult price(
            const Option& option,
            const MarketData& marketData,
            const std::string& modelName) const;

        // *** TYPE-SAFE QUERIES ***
        std::vector<ModelType> getCompatibleModelTypes(const Option& option) const;  // Fixed typo
        std::vector<ModelType> getAllModelTypes() const;  // Fixed typo

        // *** STRING QUERIES (for JSON) ***
        std::vector<std::string> getCompatibleModels(const Option& option) const;
        std::vector<std::string> getAllModels() const;

        // *** REGISTRATION: Use ModelType directly ***
        void registerModel(
            ModelType type,
            std::function<std::unique_ptr<PricingModel>()> creator);

        // *** STATIC CONVERSION UTILITIES ***
        static std::string modelTypeToString(ModelType type);
        static ModelType stringToModelType(const std::string& name);

    private:
        // *** SIMPLIFIED: Only need one map with ModelType as key ***
        std::unordered_map<ModelType, std::function<std::unique_ptr<PricingModel>()>> modelCreators_;

        void registerDefaultModels();

        // Custom hash for ModelType enum
        struct ModelTypeHash {
            std::size_t operator()(ModelType type) const {
                return static_cast<std::size_t>(type);
            }
        };
    };
}