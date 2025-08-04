#include <vector>

#include "../instruments/base/payoff.hpp"

class VanillaCallPayoff : public Payoff {
public:
    VanillaCallPayoff(double strike) : strike_(strike) {}

    double operator()(double spot) const override {
        return std::max(0.0, spot - strike_);
    }

    double operator()(const std::vector<double>& spots) const override {
        return operator()(spots[0]);
    }

    std::string getType() const override { return "vanilla_call"; }

private:
    double strike_;
};