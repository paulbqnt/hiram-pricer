#pragma once
#include <string>
#include <unordered_map>
#include <optional>

namespace pricing {

    class PricingResult {
    public:
        PricingResult(double price, std::string modelName,
                      std::unordered_map<std::string, double> greeks = {});

        // Constructor for error result
        PricingResult(std::string errorMessage, std::string modelName);

        bool hasError() const noexcept;
        const std::string& getErrorMessage() const;
        double getPrice() const;
        std::optional<double> getGreek(const std::string& name) const;
        std::string toString() const;

    private:
        double price_;
        std::string modelName_;
        std::unordered_map<std::string, double> greeks_;
        std::optional<std::string> error_;
    };

} // namespace pricing