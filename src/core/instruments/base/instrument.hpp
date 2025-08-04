#include <string>

class Instrument {
public:
    virtual ~Instrument() = default;
    virtual std::string getType() const = 0;

};