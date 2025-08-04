
#pragma once
namespace pricing {

    enum class PayoffType {
        EUROPEAN_VANILLA_CALL = 0,
        EUROPEAN_VANILLA_PUT = 1,
        AMERICAN_VANILLA_CALL = 3,
        AMERICAN_VANILLA_PUT = 4
    };

}