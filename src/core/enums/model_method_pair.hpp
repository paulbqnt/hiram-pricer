#pragma once

#include "pricing_models.hpp"
#include "numerical_methods.hpp"
#include <string>

namespace pricing {

    struct ModelMethodPair {
        PricingModel model;
        NumericalMethod method;

        bool operator==(const ModelMethodPair& other) const {
            return model == other.model  && method == other.method;
        }
    };

    struct ModelMethodPairHash {
        std::size_t operator()(const ModelMethodPair& pair) const {
            return (static_cast<std::size_t>(pair.model) << 16) |
                static_cast<std::size_t>(pair.method);
        }
    };

    std::string toString(PricingModel model);
    std::string toString(NumericalMethod method);
    std::string toString(const ModelMethodPair& pair);

    PricingModel stringToPricingModel(const std::string& str);
    NumericalMethod stringToNumericalMethod(const std::string& str);

}