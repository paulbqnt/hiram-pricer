#pragma once
#include "instrument.hpp"
#include "../../payoffs/payoff_interface.hpp"

#include <memory>

namespace pricing {
    class Payoff;

    class Option : public Instrument {
    public:
        Option(std::unique_ptr<Payoff> payoff, double timeToExpiry)
            : payoff_(std::move(payoff)), timeToExpiry_(timeToExpiry) {}

        const Payoff& getPayoff() const { return *payoff_; }
        double getTimeToExpiry() const { return timeToExpiry_; }
        double getStrike() const { return payoff_->getStrike(); }

        std::string getType() const override {
            return "Option";
        }

    private:
        std::unique_ptr<Payoff> payoff_;
        double timeToExpiry_;
    };

}