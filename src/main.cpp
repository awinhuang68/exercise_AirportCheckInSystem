#include <iostream>
#include "Flight.h"
#include "bookingDatetime.h"
#include "booking.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto f = Flight(
        "AA123",
        "American Airlines",
        "JFK",
        "LAX",
        BookingDateTime("2024-06-01 10:00:00"),
        FlightStatus::Scheduled
    );

    auto number = f.getFlightNumber();
    std::cout << "Flight Number: " << number << std::endl;

    return 0;
}
