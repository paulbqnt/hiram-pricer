#pragma once

namespace pricing {

    enum class ModelType {
        BLACK_SCHOLES = 0,
        BLACK_SCHOLES_MERTON = 1,
        BINOMIAL_TREE = 2,
        MONTE_CARLO = 3
    };


}