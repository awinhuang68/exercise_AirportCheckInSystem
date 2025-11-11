#pragma once

#include <string>
#include <iostream>
#include "bookingDatetime.h"


enum class FlightStatus
{
    Scheduled,
    Boarding,
    Departed,
    Delayed
};

class Flight
{
public:
    Flight(
        const std::string&     flightNumber,
        const std::string&     airline,
        const std::string&     departureLocation,
        const std::string&     destination,
        const BookingDateTime& departureTime,
        const FlightStatus&    flightStatus
    ) : m_flightNumber(flightNumber),
        m_airline(airline),
        m_departureLocation(departureLocation),
        m_destination(destination),
        m_departureTime(departureTime),
        m_flightStatus(flightStatus)
    {

    }

    ~Flight() {
        // std::cout << "Destructing Flight: " << std::endl;
        // std::cout << "    Flight Number     : " << m_flightNumber << std::endl;
        // std::cout << "    Airline           : " << m_airline << std::endl;
        // std::cout << "    Departure Location: " << m_departureLocation << std::endl;
        // std::cout << "    Destination       : " << m_destination << std::endl;
        // std::cout << "    Flight Status     : " << static_cast<int>(m_flightStatus) << std::endl;
    }

    auto getFlightNumber() const -> std::string {
        return m_flightNumber;
    }

    auto getAirline() const -> std::string {
        return m_airline;
    }

    auto getDepartureLocation() const -> std::string {
        return m_departureLocation;
    }

    auto getDestination() const -> std::string {
        return m_destination;
    }

    auto getDepartureTime() const -> BookingDateTime {
        return m_departureTime;
    }

    auto getFlightStatus() const -> FlightStatus {
        return m_flightStatus;
    }

    auto getFlightStatusString() const -> std::string {
        switch (m_flightStatus) {
            case FlightStatus::Scheduled:
                return "Scheduled";
            case FlightStatus::Boarding:
                return "Boarding";
            case FlightStatus::Departed:
                return "Departed";
            case FlightStatus::Delayed:
                return "Delayed";
            default:
                return "Unknown";
        }
    }

private:
    std::string     m_flightNumber;
    std::string     m_airline;
    std::string     m_departureLocation;
    std::string     m_destination;
    BookingDateTime m_departureTime;
    FlightStatus    m_flightStatus;
};
