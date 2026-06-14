#ifndef DELIVERY_H
#define DELIVERY_H

#include <iostream>
#include <string>

using namespace std;

class Delivery
{
public:
    int id;
    int customerId;
    int pickupLocation;
    int dropoffLocation;
    int priority;
    int deadline;
    double weight;
    string status;
    int assignedVehicle;

    Delivery();
    Delivery(int id, int customerId, int pickup, int dropoff, int priority, int deadline, double weight);
    
    void display() const;
    bool isOverdue(int currentTime) const;
};

#endif
