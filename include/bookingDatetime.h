#pragma once

#include <string>
#include <iostream>


class BookingDateTime
{
public:
    BookingDateTime(
        const std::string& datetime
    ) : m_datetime(datetime)
    {

    }

    ~BookingDateTime() {
        // std::cout << "Destructing BookingDateTime: " << m_datetime << std::endl;
    }

    auto getDateTime() const -> std::string {
        return m_datetime;
    }

    void setDateTime(const std::string& datetime) {
        m_datetime = datetime;
    }

private:
    std::string m_datetime;
};
