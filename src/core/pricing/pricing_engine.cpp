#include "pricing_engine.hpp"
#include "../instruments/base/option.hpp"
#include "../models/analytical/black_scholes.hpp"
#include <vector>
#include <functional>
#include <stdexcept>

namespace pricing {
    PricingEngine::PricingEngine() {
        registerDefaultModels();
    }

    // *** PRIMARY METHOD: ModelType enum ***
    PricingResult PricingEngine::price(const Option& option, const MarketData& marketData, ModelType modelType) const {
        // Check if payoff accepts this model type
        if (!option.getPayoff().acceptModel(modelType)) {
            auto compatibleTypes = getCompatibleModelTypes(option);

            std::string error = "Model '" + modelTypeToString(modelType) +
                               "' cannot price " + option.getType() + ". Compatible models: ";

            if (compatibleTypes.empty()) {
                error += "none available";
            } else {
                for (size_t i = 0; i < compatibleTypes.size(); ++i) {
                    error += modelTypeToString(compatibleTypes[i]);
                    if (i < compatibleTypes.size() - 1) error += ", ";
                }
            }

            return PricingResult(error, modelTypeToString(modelType));
        }

        // Find model creator
        auto creatorIt = modelCreators_.find(modelType);
        if (creatorIt == modelCreators_.end()) {
            return PricingResult("Model not registered: " + modelTypeToString(modelType),
                               modelTypeToString(modelType));
        }

        // Create and use model
        try {
            auto model = creatorIt->second();
            return model->price(option, marketData);
        } catch (const std::exception& e) {
            return PricingResult(std::string("Pricing error: ") + e.what(),
                               modelTypeToString(modelType));
        }
    }

    // *** SECONDARY METHOD: String delegation ***
    PricingResult PricingEngine::price(const Option& option, const MarketData& marketData, const std::string& modelName) const {
        try {
            ModelType modelType = stringToModelType(modelName);
            return price(option, marketData, modelType);  // Delegate to type-safe method
        } catch (const std::exception& e) {
            return PricingResult("Invalid model name '" + modelName + "': " + e.what(), modelName);
        }
    }

    // *** TYPE-SAFE QUERY METHODS ***
    std::vector<ModelType> PricingEngine::getCompatibleModelTypes(const Option& option) const {
        return option.getPayoff().getCompatibleModels();
    }

    std::vector<ModelType> PricingEngine::getAllModelTypes() const {
        std::vector<ModelType> types;
        types.reserve(modelCreators_.size());

        for (const auto& [type, creator] : modelCreators_) {
            types.push_back(type);
        }

        return types;
    }

    // *** STRING QUERY METHODS (convert from ModelType) ***
    std::vector<std::string> PricingEngine::getCompatibleModels(const Option& option) const {
        auto types = getCompatibleModelTypes(option);
        std::vector<std::string> names;
        names.reserve(types.size());

        for (ModelType type : types) {
            // Only include models we actually have registered
            if (modelCreators_.find(type) != modelCreators_.end()) {
                names.push_back(modelTypeToString(type));
            }
        }

        return names;
    }

    std::vector<std::string> PricingEngine::getAllModels() const {
        auto types = getAllModelTypes();
        std::vector<std::string> names;
        names.reserve(types.size());

        for (ModelType type : types) {
            names.push_back(modelTypeToString(type));
        }

        return names;
    }

    // *** REGISTRATION METHOD ***
    void PricingEngine::registerModel(ModelType type, std::function<std::unique_ptr<PricingModel>()> creator) {
        modelCreators_[type] = std::move(creator);
    }

    // *** DEFAULT MODELS REGISTRATION ***
    void PricingEngine::registerDefaultModels() {
        registerModel(ModelType::BLACK_SCHOLES,
                     []() { return std::make_unique<BlackScholesModel>(); });

        // Add more models as they're implemented:
        // registerModel(ModelType::MONTE_CARLO,
        //              []() { return std::make_unique<MonteCarloModel>(); });
    }

    // *** STATIC CONVERSION METHODS ***
    std::string PricingEngine::modelTypeToString(ModelType type) {
        switch (type) {
            case ModelType::BLACK_SCHOLES: return "blackscholes";
            case ModelType::BLACK_SCHOLES_MERTON: return "blackscholesmerton";
            case ModelType::BINOMIAL_TREE: return "binomialtree";
            case ModelType::MONTE_CARLO: return "montecarlo";
            default:
                throw std::invalid_argument("Unknown ModelType: " + std::to_string(static_cast<int>(type)));
        }
    }

    ModelType PricingEngine::stringToModelType(const std::string& name) {
        if (name == "blackscholes") return ModelType::BLACK_SCHOLES;
        if (name == "blackscholesmerton") return ModelType::BLACK_SCHOLES_MERTON;
        if (name == "binomialtree") return ModelType::BINOMIAL_TREE;
        if (name == "montecarlo") return ModelType::MONTE_CARLO;

        throw std::invalid_argument("Unknown model name: " + name);
    }
}
