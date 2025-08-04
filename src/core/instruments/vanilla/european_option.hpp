#include <memory>
#include "../base/option.hpp"
#include "../base/payoff.hpp"

class EuropeanOption : public Option {
public:
    EuropeanOption(const std::string& underlying, double strike, Date expiry, OptionType type);

    std::string getType() const override { return "european_option"; }
    bool isPathDependant() const override { return false; }
    ExerciseType getExerciseType() const override { return ExerciseType::EUROPEAN; }
private:
    std::unique_ptr<Payoff> payoff_;
};
