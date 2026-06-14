#include "../../Headers/Managers/DeliveryScheduler.h"

DeliveryScheduler::DeliveryScheduler() {}

// ========== SCHEDULING ==========

void DeliveryScheduler::scheduleDelivery(const Delivery& delivery)
{
    urgentQueue.insert(delivery);
    deadlineTree.insert(delivery);
    cout << "DeliveryScheduler: Delivery " << delivery.id
         << " scheduled (priority=" << delivery.priority
         << ", deadline=" << delivery.deadline << ")\n";
}

Delivery DeliveryScheduler::getNextUrgentDelivery()
{
    if (urgentQueue.isEmpty())
    {
        cout << "DeliveryScheduler: No pending deliveries!\n";
        return Delivery();
    }
    Delivery next = urgentQueue.extractMax();
    deadlineTree.remove(next.id);
    return next;
}

vector<Delivery> DeliveryScheduler::getDeadlineSortedDeliveries() const
{
    return deadlineTree.inorderTraversal();
}

// ========== ASSIGNMENT & UPDATES ==========

bool DeliveryScheduler::assignVehicle(int deliveryId, int vehicleId)
{
    // Update in-place within the priority queue via updatePriority (hack: search only)
    // The BST doesn't support in-place update; we remove and reinsert
    Delivery* d = deadlineTree.search(deliveryId);
    if (d == nullptr)
    {
        cout << "DeliveryScheduler: Delivery " << deliveryId << " not found!\n";
        return false;
    }
    d->assignedVehicle = vehicleId;
    d->status = "Assigned";
    cout << "DeliveryScheduler: Delivery " << deliveryId
         << " assigned to Vehicle " << vehicleId << "\n";
    return true;
}

void DeliveryScheduler::escalatePriority(int deliveryId, int newPriority)
{
    urgentQueue.updatePriority(deliveryId, newPriority);

    Delivery* d = deadlineTree.search(deliveryId);
    if (d != nullptr)
        d->priority = newPriority;
}

void DeliveryScheduler::cancelDelivery(int deliveryId)
{
    deadlineTree.remove(deliveryId);
    cout << "DeliveryScheduler: Delivery " << deliveryId << " cancelled.\n";
}

// ========== QUERIES ==========

bool DeliveryScheduler::hasPendingDeliveries() const
{
    return !urgentQueue.isEmpty();
}

int DeliveryScheduler::pendingCount() const
{
    return urgentQueue.size();
}

Delivery DeliveryScheduler::peekNextDelivery() const
{
    return urgentQueue.peek();
}

vector<Delivery> DeliveryScheduler::getOverdueDeliveries(int currentTime) const
{
    vector<Delivery> all = deadlineTree.inorderTraversal();
    vector<Delivery> overdue;
    for (const auto& d : all)
        if (d.isOverdue(currentTime))
            overdue.push_back(d);
    return overdue;
}

// ========== DISPLAY ==========

void DeliveryScheduler::display() const
{
    cout << "\n=== Delivery Scheduler ===\n";
    urgentQueue.display();
    deadlineTree.display();
}
