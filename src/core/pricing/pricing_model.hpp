// ===== core/pricing/pricing_model.hpp (Updated to avoid circular includes) =====
#pragma once
#include <string>
#include <memory>

namespace pricing {
    class Option;
    class MarketData;
    class PricingResult;
}

namespace pricing {
    class PricingModel {
    public:
        virtual ~PricingModel() = default;

        // Pure virtual pricing method
        virtual PricingResult price(const Option& option, const MarketData& marketData) = 0;

        // Model identification
        virtual std::string getName() const = 0;
        virtual std::string getVersion() const { return "1.0"; }

        // Model capabilities
        virtual bool supportsGreeks() const { return false; }
        virtual bool supportsPathDependentPayoffs() const { return false; }
        virtual bool supportsEarlyExercise() const { return false; }

        // Configuration (optional)
        virtual void configure(const std::string& configJson) {}
        virtual std::string getConfiguration() const { return "{}"; }
    };
}
