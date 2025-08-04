#pragma once
#include <string>
#include <nlohman/json.hpp>


namespace pricing::api {
    class CompatibilityHandler {
    public:
        explicit CompatibilityHandler(const CompatibilityRegistry& registry);

        // HTTP endpoint handlers
        std::string handle_get_compatibility_matrix();
        std::string handle_get_compatible_models(const std::string& style, const std::string& payoff);
        std::string handle_get_compatible_styles(const std::string& model, const std::string& payoff);
        std::string handle_get_compatible_payoffs(const std::string& model, const std::string& style);
        std::string handle_validate_combination(
            const std::string& model, const std::string& style, const std::string& payoff);

        std::string handle_batch_compatibility_check(std::string& json_body);
    private:
        const CompatibilityRegistry& registry_;

        nlohmann::json create_error_response(const std::string& error_message) const;
        nhlohmann::json create_success_response(const nhlomman::json& data) const;


    }
}