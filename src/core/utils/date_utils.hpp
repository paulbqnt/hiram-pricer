#include <chrono>
#include <stdexcept>
#include <sstream>
#include <string>

namespace hiram {
    using Date = std::chrono::year_month_day;
    using SysDays = std::chrono::sys_days;

    inline SysDays toSysDays(const Date& date) {
        return SysDays{date};
    }

    inline Date fromSysDays(const SysDays& sd) {
        return std::chrono::year_month_day{sd};
    }

    inline Date parseDate(const std::string& s) {
        std::istringstream iss(s);
        Date date;
        iss >> std::chrono::parse("%F", date);
        if (iss.fail()) throw std::runtime_error("Invalid date: " + s);
        return date;
    }

    inline std::string formatDate(const Date& d) {
        return std::chrono::format("%F", d);
    }
}
