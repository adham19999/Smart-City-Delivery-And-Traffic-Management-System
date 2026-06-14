#include "../../Headers/Models/Vehicle.h"

Vehicle::Vehicle() : id(0), capacity(0.0), speed(0.0), currentLocation(0), available(true) {}

Vehicle::Vehicle(int id, double capacity, double speed, int currentLocation, bool available)
    : id(id), capacity(capacity), speed(speed), currentLocation(currentLocation), available(available) {}

void Vehicle::display() const
{
    cout << "Vehicle " << id << ": Capacity=" << capacity << ", Speed=" << speed 
         << ", Location=" << currentLocation << ", Available=" << (available ? "Yes" : "No") << "\n";
}

bool Vehicle::canCarry(double weight) const
{
    return weight <= capacity;
}
