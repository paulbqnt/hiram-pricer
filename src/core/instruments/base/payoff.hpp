#include <string>
#include <vector>

class Payoff {
public:
    virtual ~Payoff() = default;
    virtual double operator()(double spot) const = 0;
    virtual double operator()(const std::vector<double>& spots) const = 0;
    virtual std::unique_ptr<Payoff> clone() const = 0;
    virtual std::string getType() const = 0;
    virtual double getStrike() const = 0;


};
