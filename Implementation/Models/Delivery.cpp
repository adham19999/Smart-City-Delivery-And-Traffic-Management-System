#include "../../Headers/Models/Delivery.h"

Delivery::Delivery() 
    : id(0), customerId(0), pickupLocation(0), dropoffLocation(0), 
      priority(0), deadline(0), weight(0.0), status("Pending"), assignedVehicle(-1) {}

Delivery::Delivery(int id, int customerId, int pickup, int dropoff, int priority, int deadline, double weight)
    : id(id), customerId(customerId), pickupLocation(pickup), dropoffLocation(dropoff),
      priority(priority), deadline(deadline), weight(weight), status("Pending"), assignedVehicle(-1) {}

void Delivery::display() const
{
    cout << "Delivery " << id << ": Customer=" << customerId << ", From=" << pickupLocation 
         << " To=" << dropoffLocation << ", Priority=" << priority << ", Deadline=" << deadline 
         << ", Weight=" << weight << ", Status=" << status << "\n";
}

bool Delivery::isOverdue(int currentTime) const
{
    return currentTime > deadline;
}
