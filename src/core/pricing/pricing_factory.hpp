#include "../instruments/base/instrument.hpp"
#include "../market_data/market_data.hpp"
#include "pricing_result.hpp"

class PricingModel {
public:
    virtual ~PricingModel() = default;

    virtual double price(const EuropeanOption& option, const MarketData& market) const = 0;

    virtual PricingResult priceInstrument(const Instrument& instrument const MarketData& market) const = 0;
};
