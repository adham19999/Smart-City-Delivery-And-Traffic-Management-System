#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include "../Algorithms/Sorting.h"
#include "../Algorithms/Searching.h"
#include "../Models/Delivery.h"
#include "../Models/Location.h"
#include <vector>
#include <iostream>
using namespace std;

// Component 6: Data Processing Module (Divide & Conquer)
class DataProcessor
{
public:
    DataProcessor() = default;

    vector<Delivery> sortByDeadline(vector<Delivery> deliveries);
    vector<Delivery> sortByPriority(vector<Delivery> deliveries);
    vector<Delivery> sortByWeight(vector<Delivery> deliveries);

    int findDeliveryByDeadline(const vector<Delivery>& sorted, int deadline);
    int findDeliveryById(const vector<Delivery>& sorted, int id);

    pair<pair<Location, Location>, double> findClosestDeliveryPair(vector<Location> locations);

    double averageDeliveryWeight(const vector<Delivery>& deliveries) const;
    vector<Delivery> filterByStatus(const vector<Delivery>& deliveries, const string& status) const;
    vector<Delivery> filterOverdue(const vector<Delivery>& deliveries, int currentTime) const;
    vector<Delivery> mergeSortedLists(const vector<Delivery>& a, const vector<Delivery>& b,
                                      const string& criterion = "deadline") const;
    vector<Delivery> topKByPriority(vector<Delivery> deliveries, int k);

    void displayReport(const vector<Delivery>& deliveries) const;
};

#endif // DATAPROCESSOR_H
