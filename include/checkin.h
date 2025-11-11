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

    ERR_CODE Process(const Booking& booking);
    
    ERR_CODE CheckBookingID(const std::string& bookingID);
    
    ERR_CODE CheckFlightNumber(const std::string& flightNumber);
    
    ERR_CODE CheckSeatNumber(const std::string& seatNumber);
    
    ERR_CODE CheckBookingStatus(BookingStatus status);

private:
    std::string m_checkID;
    std::string m_bookID;
    std::string m_flightNumber;
    std::time_t m_checkInTime;
    CheckInStatus m_checkInStatus;
    std::string m_staffID;
};
