#pragma once

namespace pricing {
    enum class NumericalMethod {
        ANALYTICAL,
        MONTE_CARLO,
        BINOMIAL_TREE,
        TRINOMIAL_TREE,
        FINITE_DIFFERENCE
    };
}