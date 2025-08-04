#pragma once

namespace pricing {
    class MarketData {
    private:
        double spotPrice;
        double volatility;
        double riskFreeRate;
        double dividendYield;

    public:
        MarketData(double spot = 100.0, double vol = 0.2, double rate = 0.05, double div = 0.0)
            : spotPrice(spot), volatility(vol), riskFreeRate(rate), dividendYield(div) {}

        double getSpotPrice() const { return spotPrice; }
        double getVolatility() const { return volatility; }
        double getRiskFreeRate() const { return riskFreeRate; }
        double getDividendYield() const { return dividendYield; }

        void setSpotPrice(double spot) { spotPrice = spot; }
        void setVolatility(double vol) { volatility = vol; }
        void setRiskFreeRate(double rate) { riskFreeRate = rate; }
        void setDividendYield(double div) { dividendYield = div; }

    };
}

