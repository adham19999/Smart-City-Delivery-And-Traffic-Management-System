#ifndef SEARCHING_H
#define SEARCHING_H

#include "../Models/Delivery.h"
#include "../Models/Location.h"
#include <vector>
#include <iostream>
#include <utility>
using namespace std;

class Searching
{
public:
    // Binary Search: O(log n) — requires sorted input
    // Searches by deadline in a deadline-sorted vector
    static int binarySearchByDeadline(const vector<Delivery>& sorted, int deadline);
    // Searches by ID in an ID-sorted vector
    static int binarySearchById(const vector<Delivery>& sorted, int id);

    // Closest Pair of Points (Divide & Conquer): O(n log n)
    // Returns the two closest locations and their distance
    static pair<pair<Location, Location>, double> closestPair(vector<Location>& locations);

    // Linear search by delivery ID (for unsorted data)
    static int linearSearchById(const vector<Delivery>& deliveries, int id);

private:
    static double dist(const Location& a, const Location& b);
    static pair<pair<Location, Location>, double> closestPairRec(
        vector<Location>& pts, int left, int right);
    static pair<pair<Location, Location>, double> stripClosest(
        vector<Location>& strip, double d);
};

#endif // SEARCHING_H
