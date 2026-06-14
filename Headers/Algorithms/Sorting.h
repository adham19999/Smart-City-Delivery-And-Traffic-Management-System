#ifndef SORTING_H
#define SORTING_H

#include "../Models/Delivery.h"
#include <vector>
#include <iostream>
using namespace std;

class Sorting
{
public:
    // MergeSort: O(n log n) — stable, good for external sort and multi-criteria
    static void mergeSort(vector<Delivery>& deliveries, const string& criterion = "deadline");
    static void mergeSortVehicleId(vector<int>& ids);

    // QuickSort: O(n log n) avg — fast for large in-memory datasets
    static void quickSort(vector<Delivery>& deliveries, int low, int high, const string& criterion = "priority");

    // Display helper
    static void displaySorted(const vector<Delivery>& deliveries, const string& label = "Sorted Deliveries");

private:
    static void mergeSortHelper(vector<Delivery>& arr, int left, int right, const string& criterion);
    static void merge(vector<Delivery>& arr, int left, int mid, int right, const string& criterion);

    static int partition(vector<Delivery>& arr, int low, int high, const string& criterion);
    static bool compare(const Delivery& a, const Delivery& b, const string& criterion);
};

#endif // SORTING_H
