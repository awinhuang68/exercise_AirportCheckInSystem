#pragma once

#include <string>
#include <iostream>


enum class BookingStatus {
    Booked,
    CheckedIn,
    Cancelled
};


class Booking
{
public:
    Booking(
        const std::string&   bookingID,
        const std::string&   flightNumber,
        const std::string&   seatNumber,
        const BookingStatus& bookingStatus
    ) : m_bookingID(bookingID),
        m_flightNumber(flightNumber),
        m_seatNumber(seatNumber),
        m_bookingStatus(bookingStatus)
    {

    }

    ~Booking() {
        std::cout << "Destructing Booking: " << std::endl;
        std::cout << "    Booking ID    : " << m_bookingID << std::endl;
        std::cout << "    Flight Number : " << m_flightNumber << std::endl;
        std::cout << "    Seat Number   : " << m_seatNumber << std::endl;
        std::cout << "    Booking Status: " << static_cast<int>(m_bookingStatus) << std::endl;
    }

    auto getBookingID() const -> std::string {
        return m_bookingID;
    }

    auto getFlightNumber() const -> std::string {
        return m_flightNumber;
    }

    auto getSeatNumber() const -> std::string {
        return m_seatNumber;
    }

    auto getBookingStatus() const -> BookingStatus {
        return m_bookingStatus;
    }

private:
    std::string     m_bookingID;
    std::string     m_flightNumber;
    std::string     m_seatNumber;
    BookingStatus   m_bookingStatus;
};
