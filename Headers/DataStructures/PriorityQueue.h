#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "../Models/Delivery.h"
#include <vector>
#include <iostream>

using namespace std;

class DeliveryPriorityQueue
{
private:
    vector<Delivery> heap;
    
    // Helper functions
    int parent(int i) const;
    int leftChild(int i) const;
    int rightChild(int i) const;
    void heapifyUp(int i);
    void heapifyDown(int i);
    
public:
    DeliveryPriorityQueue();
    ~DeliveryPriorityQueue() = default;
    
    // Core operations
    void insert(const Delivery& delivery);
    Delivery extractMax();      // Extract highest priority delivery
    Delivery extractMin();      // Extract lowest priority delivery
    Delivery peek() const;      // View highest priority without removing
    
    // Utility operations
    bool isEmpty() const;
    int size() const;
    void updatePriority(int deliveryId, int newPriority);
    void display() const;
    void clear();
};

#endif // PRIORITYQUEUE_H
