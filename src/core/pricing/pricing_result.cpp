#include "pricing_result.hpp"
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iomanip>

namespace pricing {

PricingResult::PricingResult(double price, std::string modelName,
                             std::unordered_map<std::string, double> greeks)
    : price_(price), modelName_(std::move(modelName)), greeks_(std::move(greeks)), error_(std::nullopt) {
    if (std::isnan(price_) || std::isinf(price_) || price_ < 0) {
        throw std::invalid_argument("Invalid price value");
    }
    for (const auto& [name, val] : greeks_) {
        if (std::isnan(val) || std::isinf(val)) {
            throw std::invalid_argument("Invalid Greek value: " + name);
        }
    }
}

// Constructor for error result
PricingResult::PricingResult(std::string errorMessage, std::string modelName)
    : price_(0), modelName_(std::move(modelName)), greeks_(), error_(std::move(errorMessage)) {
    if (error_->empty()) {
        throw std::invalid_argument("Error message cannot be empty");
    }
}

bool PricingResult::hasError() const noexcept {
    return error_.has_value();
}

const std::string& PricingResult::getErrorMessage() const {
    if (!error_) throw std::runtime_error("No error present");
    return *error_;
}

double PricingResult::getPrice() const {
    if (hasError()) throw std::runtime_error("Cannot get price from error result");
    return price_;
}

std::optional<double> PricingResult::getGreek(const std::string& name) const {
    if (hasError()) return std::nullopt;
    auto it = greeks_.find(name);
    if (it != greeks_.end()) return it->second;
    return std::nullopt;
}

std::string PricingResult::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4);
    if (hasError()) {
        oss << "ERROR [" << modelName_ << "]: " << *error_;
    } else {
        oss << "SUCCESS [" << modelName_ << "]: Price = $" << price_;
        if (!greeks_.empty()) {
            oss << " | Greeks: ";
            bool first = true;
            for (const auto& [name, val] : greeks_) {
                if (!first) oss << ", ";
                oss << name << "=" << val;
                first = false;
            }
        }
    }
    return oss.str();
}

} // namespace pricing
