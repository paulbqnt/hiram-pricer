#include "model_method_pair.hpp"
#include <stdexcept>
#include <algorithm>
#include <cctype>




namespace pricing {

// ==========================================
// PricingModel to String
// ==========================================
std::string toString(PricingModel model) {
    switch (model) {
        case PricingModel::BLACK_SCHOLES: 
            return "Black-Scholes";
        case PricingModel::BLACK_SCHOLES_MERTON: 
            return "Black-Scholes-Merton";
        case PricingModel::HESTON: 
            return "Heston";
        default:
            throw std::invalid_argument(
                "Unknown PricingModel: " + 
                std::to_string(static_cast<int>(model))
            );
    }
}

// ==========================================
// NumericalMethod to String
// ==========================================
std::string toString(NumericalMethod method) {
    switch (method) {
        case NumericalMethod::ANALYTICAL: 
            return "Analytical";
        case NumericalMethod::MONTE_CARLO: 
            return "Monte Carlo";
        case NumericalMethod::BINOMIAL_TREE: 
            return "Binomial Tree";
        case NumericalMethod::TRINOMIAL_TREE: 
            return "Trinomial Tree";
        case NumericalMethod::FINITE_DIFFERENCE: 
            return "Finite Difference";
        default:
            throw std::invalid_argument(
                "Unknown NumericalMethod: " + 
                std::to_string(static_cast<int>(method))
            );
    }
}

// ==========================================
// ModelMethodPair to String
// ==========================================
std::string toString(const ModelMethodPair& pair) {
    return toString(pair.model) + " + " + toString(pair.method);
}

// ==========================================
// String to PricingModel (case-insensitive)
// ==========================================
PricingModel stringToPricingModel(const std::string& str) {
    // Convert to lowercase for case-insensitive matching
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), 
                   [](unsigned char c){ return std::tolower(c); });
    
    if (lower == "blackscholes" || lower == "black-scholes" || 
        lower == "bs" || lower == "black_scholes") {
        return PricingModel::BLACK_SCHOLES;
    }
    if (lower == "blackscholesmerton" || lower == "black-scholes-merton" || 
        lower == "bsm" || lower == "black_scholes_merton") {
        return PricingModel::BLACK_SCHOLES_MERTON;
    }
    if (lower == "heston") {
        return PricingModel::HESTON;
    }

    throw std::invalid_argument("Unknown pricing model: " + str);
}

// ==========================================
// String to NumericalMethod (case-insensitive)
// ==========================================
NumericalMethod stringToNumericalMethod(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), 
                   [](unsigned char c){ return std::tolower(c); });
    
    if (lower == "analytical" || lower == "analytic" || 
        lower == "closedform" || lower == "closed-form" || 
        lower == "closed_form") {
        return NumericalMethod::ANALYTICAL;
    }
    if (lower == "montecarlo" || lower == "monte-carlo" || 
        lower == "mc" || lower == "monte_carlo") {
        return NumericalMethod::MONTE_CARLO;
    }
    if (lower == "binomialtree" || lower == "binomial-tree" || 
        lower == "binomial" || lower == "binomial_tree") {
        return NumericalMethod::BINOMIAL_TREE;
    }
    if (lower == "trinomialtree" || lower == "trinomial-tree" || 
        lower == "trinomial" || lower == "trinomial_tree") {
        return NumericalMethod::TRINOMIAL_TREE;
    }
    if (lower == "finitedifference" || lower == "finite-difference" || 
        lower == "fd" || lower == "pde" || lower == "finite_difference") {
        return NumericalMethod::FINITE_DIFFERENCE;
    }
    
    throw std::invalid_argument("Unknown numerical method: " + str);
}

} // namespace pricing