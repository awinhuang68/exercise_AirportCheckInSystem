#include <string>


enum class FlightStatus
{
    Scheduled,
    Boarding,
    Departed,
    Delayed
};

class DateTime
{
    // Placeholder for DateTime class implementation
};

class Flight
{
public:
    Flight(
        const std::string&  flightNumber,
        const std::string&  airline,
        const std::string&  departureLocation,
        const std::string&  destination,
        const DateTime&     departureTime,
        const FlightStatus& flightStatus
    ) : m_flightNumber(flightNumber),
        m_airline(airline),
        m_departureLocation(departureLocation),
        m_destination(destination),
        m_departureTime(departureTime),
        m_flightStatus(flightStatus)
    {

    }

    ~Flight() {

    }

    auto getFlightNumber() const -> std::string {
        return m_flightNumber;
    }

private:
    std::string  m_flightNumber;
    std::string  m_airline;
    std::string  m_departureLocation;
    std::string  m_destination;
    DateTime     m_departureTime;
    FlightStatus m_flightStatus;
};
