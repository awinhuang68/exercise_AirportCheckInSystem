#include "checkin.h"
#include <memory>
#include <regex>



ERR_CODE CheckIn::Process(const std::unique_ptr<Booking>& booking)
{
    ERR_CODE bookingIdResult = CheckBookingID(booking->getBookingID());
    ERR_CODE flightNumberResult = CheckFlightNumber(booking->getFlightNumber());
    ERR_CODE seatNumberResult = CheckSeatNumber(booking->getSeatNumber());
    ERR_CODE bookingStatusResult = CheckBookingStatus(booking->getBookingStatus());

    if (bookingIdResult == ERR_CODE::SUCCESS &&
        flightNumberResult == ERR_CODE::SUCCESS &&
        seatNumberResult == ERR_CODE::SUCCESS &&
        bookingStatusResult == ERR_CODE::SUCCESS)
    {
        m_bookID = booking->getBookingID();
        m_flightNumber = booking->getFlightNumber();
        m_checkInTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        m_checkInStatus = CheckInStatus::Completed;

        // Booking's status to "Checked-in"
        booking->setBookingStatus(BookingStatus::CheckedIn);
        return ERR_CODE::SUCCESS;
    }

    m_checkInStatus = CheckInStatus::Failed;

    // Return the first error encountered
    if (bookingIdResult != ERR_CODE::SUCCESS) return bookingIdResult;
    if (flightNumberResult != ERR_CODE::SUCCESS) return flightNumberResult;
    if (seatNumberResult != ERR_CODE::SUCCESS) return seatNumberResult;
    return bookingStatusResult;
}

ERR_CODE CheckIn::CheckBookingID(const std::string& bookingID)
{
    // Check if string length is exactly 15 characters
    if (bookingID.length() != 14) {
        printf("Booking ID(%s) length invalid: %zu\n", bookingID.c_str(), bookingID.length());
        return ERR_CODE::INVALID_BOOKING_ID;
    }

    // Use smart pointer for regex pattern
    auto pattern = std::make_unique<std::regex>(R"(^BKG\d{8}\d{3}$)");

    // Check if format matches BKG + 8 digits (YYYYMMDD) + 3 digits
    if (!std::regex_match(bookingID, *pattern)) {
        printf("Booking ID(%s) format invalid.\n", bookingID.c_str());
        return ERR_CODE::INVALID_BOOKING_ID;
    }

    // Extract and validate the date part (YYYYMMDD)
    std::string dateStr = bookingID.substr(3, 8);

    // Use smart pointer for date validation
    auto datePattern = std::make_unique<std::regex>(R"(^(19|20)\d{2}(0[1-9]|1[0-2])(0[1-9]|[12]\d|3[01])$)");

    if (!std::regex_match(dateStr, *datePattern)) {
        printf("Booking ID(%s) date format invalid.\n", bookingID.c_str());
        return ERR_CODE::INVALID_BOOKING_ID;
    }

    // Additional date validation
    int year = std::stoi(dateStr.substr(0, 4));
    int month = std::stoi(dateStr.substr(4, 2));
    int day = std::stoi(dateStr.substr(6, 2));

    // Basic month/day validation
    if (month < 1 || month > 12) {
        printf("Booking ID(%s) month invalid: %d\n", bookingID.c_str(), month);
        return ERR_CODE::INVALID_BOOKING_ID;
    }

    if (day < 1 || day > 31) {
        printf("Booking ID(%s) day invalid: %d\n", bookingID.c_str(), day);
        return ERR_CODE::INVALID_BOOKING_ID;
    }

    // February validation
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            printf("Booking ID(%s) day invalid for February: %d\n", bookingID.c_str(), day);
            return ERR_CODE::INVALID_BOOKING_ID;
        }
    }

    // Months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        printf("Booking ID(%s) day invalid for month %d: %d\n", bookingID.c_str(), month, day);
        return ERR_CODE::INVALID_BOOKING_ID;
    }

    return ERR_CODE::SUCCESS; // Valid booking ID
}

ERR_CODE CheckIn::CheckFlightNumber(const std::string& flightNumber)
{
    // Check if string length is between 2-8 characters
    if (flightNumber.length() < 2 || flightNumber.length() > 8) {
        return ERR_CODE::INVALID_FLIGHT_NUMBER;
    }

    // Use smart pointer for regex pattern to validate alphanumeric characters
    auto pattern = std::make_unique<std::regex>(R"(^[A-Za-z0-9]{2,8}$)");

    // Check if format matches 2-8 alphanumeric characters
    if (!std::regex_match(flightNumber, *pattern)) {
        return ERR_CODE::INVALID_FLIGHT_NUMBER;
    }

    return ERR_CODE::SUCCESS; // Valid flight number
}

ERR_CODE CheckIn::CheckSeatNumber(const std::string& seatNumber)
{
    // Check if string length is between 2-3 characters
    if (seatNumber.length() < 2 || seatNumber.length() > 3) {
        printf("Seat number(%s) length invalid: %zu\n", seatNumber.c_str(), seatNumber.length());
        return ERR_CODE::INVALID_SEAT_NUMBER;
    }

    // Use smart pointer for regex pattern to validate row number + letter format
    auto pattern = std::make_unique<std::regex>(R"(^[1-9]\d*[A-Za-z]$)");

    // Check if format matches row number (1-99) + letter (A-Z)
    if (!std::regex_match(seatNumber, *pattern)) {
        printf("Seat number(%s) format invalid.\n", seatNumber.c_str());
        return ERR_CODE::INVALID_SEAT_NUMBER;
    }

    return ERR_CODE::SUCCESS; // Valid seat number
}

ERR_CODE CheckIn::CheckBookingStatus(BookingStatus status)
{
    // Use smart pointer for status validation logic
    auto statusValidator = std::make_unique<bool>(status == BookingStatus::Booked);

    // Check if status is "Booked"
    // Only "Booked" status is valid for check-in
    // "CheckedIn" and "Cancelled" statuses should return failure
    if (*statusValidator) {
        return ERR_CODE::SUCCESS; // Valid: Booked status
    }

    return ERR_CODE::INVALID_BOOKING_STATUS; // Invalid: CheckedIn or Cancelled
}
