#pragma once
#include <string>
#include <memory>

namespace pricing {
    class Option;
    class MarketData;
    class PricingResult;
}

namespace pricing {
    class PricingImplementation {
    public:
        virtual ~PricingImplementation() = default;

        virtual PricingResult price(const Option& option, const MarketData& marketData) = 0;

        virtual std::string getName() const = 0;
        virtual std::string getVersion() const { return "1.0"; }

        // Model capabilities
        virtual bool supportsGreeks() const { return false; }
    };
}
