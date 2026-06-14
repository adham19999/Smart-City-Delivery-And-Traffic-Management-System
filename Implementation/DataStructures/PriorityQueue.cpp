#include "../../Headers/DataStructures/PriorityQueue.h"
#include <algorithm>

DeliveryPriorityQueue::DeliveryPriorityQueue() {}

// ========== HELPER FUNCTIONS ==========

int DeliveryPriorityQueue::parent(int i) const
{
    return (i - 1) / 2;
}

int DeliveryPriorityQueue::leftChild(int i) const
{
    return 2 * i + 1;
}

int DeliveryPriorityQueue::rightChild(int i) const
{
    return 2 * i + 2;
}

void DeliveryPriorityQueue::heapifyUp(int i)
{
    // Move element up if priority is higher than parent (max-heap)
    while (i > 0 && heap[parent(i)].priority < heap[i].priority)
    {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void DeliveryPriorityQueue::heapifyDown(int i)
{
    // Move element down to maintain max-heap property
    int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);
    
    if (left < heap.size() && heap[left].priority > heap[largest].priority)
        largest = left;
    
    if (right < heap.size() && heap[right].priority > heap[largest].priority)
        largest = right;
    
    if (largest != i)
    {
        swap(heap[i], heap[largest]);
        heapifyDown(largest);
    }
}

// ========== CORE OPERATIONS ==========

void DeliveryPriorityQueue::insert(const Delivery& delivery)
{
    heap.push_back(delivery);
    heapifyUp(heap.size() - 1);
    
    cout << "Delivery " << delivery.id << " (Priority: " << delivery.priority << ") inserted into queue.\n";
}

Delivery DeliveryPriorityQueue::extractMax()
{
    if (isEmpty())
    {
        cout << "Error: Queue is empty!\n";
        return Delivery();
    }
    
    Delivery maxDelivery = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    
    if (!isEmpty())
        heapifyDown(0);
    
    cout << "Extracted highest priority delivery " << maxDelivery.id << " (Priority: " 
         << maxDelivery.priority << ")\n";
    
    return maxDelivery;
}

Delivery DeliveryPriorityQueue::extractMin()
{
    if (isEmpty())
    {
        cout << "Error: Queue is empty!\n";
        return Delivery();
    }
    
    // Find minimum (lowest priority) element
    int minIdx = 0;
    for (int i = 1; i < heap.size(); i++)
    {
        if (heap[i].priority < heap[minIdx].priority)
            minIdx = i;
    }
    
    Delivery minDelivery = heap[minIdx];
    heap[minIdx] = heap[heap.size() - 1];
    heap.pop_back();
    
    // Restore heap property
    if (minIdx < heap.size())
    {
        heapifyUp(minIdx);
        heapifyDown(minIdx);
    }
    
    cout << "Extracted lowest priority delivery " << minDelivery.id << " (Priority: " 
         << minDelivery.priority << ")\n";
    
    return minDelivery;
}

Delivery DeliveryPriorityQueue::peek() const
{
    if (isEmpty())
    {
        cout << "Error: Queue is empty!\n";
        return Delivery();
    }
    
    return heap[0];
}

// ========== UTILITY OPERATIONS ==========

bool DeliveryPriorityQueue::isEmpty() const
{
    return heap.empty();
}

int DeliveryPriorityQueue::size() const
{
    return heap.size();
}

void DeliveryPriorityQueue::updatePriority(int deliveryId, int newPriority)
{
    int idx = -1;
    
    // Find delivery by ID
    for (int i = 0; i < heap.size(); i++)
    {
        if (heap[i].id == deliveryId)
        {
            idx = i;
            break;
        }
    }
    
    if (idx == -1)
    {
        cout << "Error: Delivery " << deliveryId << " not found in queue!\n";
        return;
    }
    
    int oldPriority = heap[idx].priority;
    heap[idx].priority = newPriority;
    
    // Restore heap property
    if (newPriority > oldPriority)
        heapifyUp(idx);
    else if (newPriority < oldPriority)
        heapifyDown(idx);
    
    cout << "Updated delivery " << deliveryId << " priority from " << oldPriority 
         << " to " << newPriority << "\n";
}

void DeliveryPriorityQueue::display() const
{
    if (isEmpty())
    {
        cout << "\n=== Priority Queue (Empty) ===\n";
        return;
    }
    
    cout << "\n=== Priority Queue Contents ===\n";
    cout << "Position | DeliveryID | Priority | Customer | Status\n";
    cout << "---------|------------|----------|----------|--------\n";
    
    for (int i = 0; i < heap.size(); i++)
    {
        cout << i << "        | " 
             << heap[i].id << "          | "
             << heap[i].priority << "        | "
             << heap[i].customerId << "       | "
             << heap[i].status << "\n";
    }
    
    cout << "\nHeap Structure (Array): ";
    for (int i = 0; i < heap.size(); i++)
    {
        cout << "(" << heap[i].id << ":" << heap[i].priority << ") ";
    }
    cout << "\n";
}

void DeliveryPriorityQueue::clear()
{
    heap.clear();
    cout << "Priority queue cleared.\n";
}
