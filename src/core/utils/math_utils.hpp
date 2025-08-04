#include <bits/valarray_after.h>
#include <cmath>

class MathUtils {
public:
    static double normalCDF(double x) {
        if (x < 0) {
            return 1.0 - normalCDF(-x);
        }

        const double a1 = 0.254829592;
        const double a2 = -0.284496736;
        const double a3 = 1.421413741;
        const double a4 = -1.453152027;
        const double a5 = 1.061405429;
        const double p = 0.3275911;

        double t = 1.0 / (1.0 + p * x);
        double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * std::exp(-x * x);
        return y;

    }
    static double normalPDF(double x) {
        return std::exp(-0.5 * x * x) / std::sqrt(2.0 * 3.14);
    }

};
