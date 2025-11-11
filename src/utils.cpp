#include "utils.h"

auto getDatetimeNowString() -> std::string {
    // Get current date time and convert to string
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y%m%d", std::localtime(&now));
    return std::string(buf);
}
