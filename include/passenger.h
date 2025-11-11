#include <string>
#include <iostream>


class Passenger
{
public:
    Passenger(
        const std::string& id
    ) : id(id)
    {
        std::cout << "Constructing Passenger: " << id << std::endl;
    }

    ~Passenger() {
        std::cout << "Destructing Passenger: " << id << std::endl;
    }

private:
    std::string id;
};
