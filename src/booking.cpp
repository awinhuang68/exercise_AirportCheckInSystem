#include "booking.h"
#include "utils.h"


std::unique_ptr<Booking> createBooking(
    const std::unique_ptr<Passenger>& passenger,
    const std::shared_ptr<Flight>& flight
)
{
    // Booking ID = depature city of flight + YYYYMMDD + 3 digits
    std::string nowDatetimeString = getDatetimeNowString();
    // std::string bookingID = flight->getDepartureLocation() + nowDatetimeString + "001";
    std::string bookingID = "BKG" + nowDatetimeString + "001";
    std::string flightNumber = flight->getFlightNumber();
    std::string seatNumber = "1A"; // Default seat number
    BookingStatus bookingStatus = BookingStatus::Booked;
    return std::make_unique<Booking>(bookingID, flightNumber, seatNumber, bookingStatus);
}
