#pragma once

#include "booking.h"
#include <string>
#include <ctime>
#include <chrono>

enum class CheckInStatus {
    Pending,
    Completed,
    Failed
};

enum class ERR_CODE {
    SUCCESS,
    INVALID_BOOKING_ID,
    INVALID_FLIGHT_NUMBER,
    INVALID_SEAT_NUMBER,
    INVALID_BOOKING_STATUS
};

class CheckIn
{
public:
     // Constructor with RAII initialization
    CheckIn() : m_checkID{},
                m_bookID{},
                m_flightNumber{},
                m_checkInTime{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())},
                m_checkInStatus{CheckInStatus::Pending},
                m_staffID{} {}

    // Destructor
    ~CheckIn() = default;

    ERR_CODE Process(const std::unique_ptr<Booking>& booking);

    ERR_CODE CheckBookingID(const std::string& bookingID);

    ERR_CODE CheckFlightNumber(const std::string& flightNumber);

    ERR_CODE CheckSeatNumber(const std::string& seatNumber);

    ERR_CODE CheckBookingStatus(BookingStatus status);

    auto getCheckInId() const -> std::string {
        return m_checkID;
    }

    auto getBookingId() const -> std::string {
        return m_bookID;
    }

    auto getFlightNumber() const -> std::string {
        return m_flightNumber;
    }

    auto getCheckInTime() const -> std::string {
        std::string checkInTimeString;

        // Convert m_checkInTime(std::time_t) to std::string
        tm *ltm = std::localtime(&m_checkInTime);
        char mbstr[100];
        std::strftime(mbstr, 100, "%Y%m%d", std::localtime(&m_checkInTime));
        std::string dateString (mbstr);

        return dateString;
    }

    auto getCheckInStatus() const -> CheckInStatus {
        return m_checkInStatus;
    }

    auto getStaffID() const -> std::string {
        return m_staffID;
    }

private:
    std::string m_checkID;
    std::string m_bookID;
    std::string m_flightNumber;
    std::time_t m_checkInTime;
    CheckInStatus m_checkInStatus;
    std::string m_staffID;
};
