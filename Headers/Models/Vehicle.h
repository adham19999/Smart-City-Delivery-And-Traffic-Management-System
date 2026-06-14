#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

using namespace std;

class Vehicle
{
public:
    int id;
    double capacity;
    double speed;
    int currentLocation;
    bool available;

    Vehicle();
    Vehicle(int id, double capacity, double speed, int currentLocation, bool available);
    
    void display() const;
    bool canCarry(double weight) const;
};

#endif
