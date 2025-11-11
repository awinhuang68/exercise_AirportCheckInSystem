#include <iostream>
#include "Flight.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto f = Flight(
        "AA123",
        "American Airlines",
        "JFK",
        "LAX",
        DateTime(),
        FlightStatus::Scheduled
    );

    auto number = f.getFlightNumber();
    std::cout << "Flight Number: " << number << std::endl;

    return 0;
}
