#ifndef DELIVERYSCHEDULER_H
#define DELIVERYSCHEDULER_H

#include "../DataStructures/PriorityQueue.h"
#include "../DataStructures/BST.h"
#include "../Models/Delivery.h"
#include "../Models/Vehicle.h"
#include <vector>
#include <iostream>
using namespace std;

// Component 4: Delivery Scheduler (Priority Queue + BST)
// Uses PriorityQueue to process urgent deliveries first
// Uses BST to maintain deadline-sorted view
class DeliveryScheduler
{
private:
    DeliveryPriorityQueue urgentQueue;
    DeliveryBST deadlineTree;

public:
    DeliveryScheduler();

    void scheduleDelivery(const Delivery& delivery);
    Delivery getNextUrgentDelivery();
    vector<Delivery> getDeadlineSortedDeliveries() const;

    bool assignVehicle(int deliveryId, int vehicleId);
    void escalatePriority(int deliveryId, int newPriority);
    void cancelDelivery(int deliveryId);

    bool hasPendingDeliveries() const;
    int pendingCount() const;
    Delivery peekNextDelivery() const;
    vector<Delivery> getOverdueDeliveries(int currentTime) const;

    void display() const;
};

#endif // DELIVERYSCHEDULER_H
