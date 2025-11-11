#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include "Flight.h"
#include "bookingDatetime.h"
#include "booking.h"
#include "passenger.h"


using PassengerPtr = std::shared_ptr<Passenger>;
using FlightPtr = std::shared_ptr<Flight>;
using BookingPtr = std::shared_ptr<Booking>;
using PassengerPtr = std::shared_ptr<Passenger>;
using FlightList = std::vector<FlightPtr>;
using BookingList = std::vector<BookingPtr>;
using PassengerList = std::vector<PassengerPtr>;


FlightList flights;
std::weak_ptr<Flight> choosenFlight;
PassengerPtr passenger;



void initFlightData() {
    std::array airlines = {
        "American Airlines",
        "Delta Airlines",
        "United Airlines",
        "Southwest Airlines",
        "JetBlue Airways"
    };

    std::array DepartureCities = {
        "TPE",
        "HKG",
        "NRT",
        "OKA",
        "BKK"
    };

    std::array DestinationCities = {
        "LAX",
        "JFK",
        "SFO",
        "ORD",
        "MIA"
    };

    // Random generate 5 flight data
    for (int i = 0; i < 5; ++i) {
        std::string flyNumber = "FL" + std::to_string(100 + i);
        std::string airline = airlines[i % airlines.size()];
        std::string departureCity = DepartureCities[i % DepartureCities.size()];
        std::string destinationCity = DestinationCities[i % DestinationCities.size()];
        std::string bookingTime = "2024-06-0" + std::to_string(i + 1) + " 10:00:00";

        auto flight = std::make_shared<Flight>(
            flyNumber,
            airline,
            departureCity,
            destinationCity,
            BookingDateTime(bookingTime),
            FlightStatus::Scheduled
        );
        flights.push_back(flight);
    }
}

void showFlightData() {
    printf("Flight \t Number \t Airline \t From \t To \t Departure Time \t Status\n");
    for (size_t i = 0; i < flights.size(); ++i) {
        printf("%zu \t %s \t %s \t %s \t %s \t %s \t %s\n",
                i,
                flights[i]->getFlightNumber().c_str(),
                flights[i]->getAirline().c_str(),
                flights[i]->getDepartureLocation().c_str(),
                flights[i]->getDestination().c_str(),
                flights[i]->getDepartureTime().getDateTime().c_str(),
                flights[i]->getFlightStatusString().c_str());
    }
}

void chooseFlight() {
    while (true) {
        printf("\n\nEnter flight number: ");
        // Get input
        std::string command;
        std::cin >> command;

        // Convert command to int
        int userChooseFlightNumber = -1;
        try {
            userChooseFlightNumber = std::stoi(command);
        } catch (const std::invalid_argument& ia) {
            printf("Invalid flight number.\n");
            continue;
        }

        if (userChooseFlightNumber < 0 || userChooseFlightNumber >= static_cast<int>(flights.size())) {
            printf("Invalid flight number.\n");
        } else {
            choosenFlight = flights[userChooseFlightNumber];
            printf("Chosen flight number: %s\n", choosenFlight.lock()->getFlightNumber().c_str());
            break;
        }
    }
}

void doBooking() {
    if (choosenFlight.expired()) {
        printf("No flight chosen. Please choose a flight first.\n");
        return;
    }

    // Simulate booking process
    printf("Booking flight number: %s\n", choosenFlight.lock()->getFlightNumber().c_str());
}

void doCheckIn() {
    if (choosenFlight.expired()) {
        printf("No flight chosen. Please choose a flight first.\n");
        return;
    }

    // Simulate check-in process
    printf("Checking in for flight number: %s\n", choosenFlight.lock()->getFlightNumber().c_str());
}

void showStatus() {
    if (passenger) {
        printf("Passenger ID: %s\n", passenger->getID().c_str());
    } else {
        printf("No Passenger\n");
    }

    if (!choosenFlight.expired()) {
        printf("Chosen Flight Number: %s, status: %s\n",
            choosenFlight.lock()->getFlightNumber().c_str(),
            choosenFlight.lock()->getFlightStatusString().c_str());
    } else {
        printf("No Flight Chosen\n");
    }
}

int main() {
    initFlightData();

    // Create passenger data
    printf("Enter passenger ID: \n");
    // Get input
    std::string passengerId;
    std::cin >> passengerId;
    passenger = std::make_shared<Passenger>(passengerId);

    while (true) {
        // Prompt user for input
        printf("\n\nEnter a command: \n");
        printf(" 1: List Flights\n");
        printf(" 2: Book Flight\n");
        printf(" 3: Check-in\n");
        printf(" 4: status\n");
        printf(" q: Quit\n");
        printf("Your choice: ");

        // Get input
        std::string command;
        std::cin >> command;
        // printf("User input: %s\n", command.c_str());
        if (command == "q") {
            printf("Exiting program.\n");
            break;
        }

        if (command == "1") {
            showFlightData();
            chooseFlight();
        } else if (command == "2") {
            doBooking();
        } else if (command == "3") {
            doCheckIn();
        } else if (command == "4") {
            showStatus();
        }
    }

    return 0;
}
