#include "../../Headers/Managers/DataProcessor.h"
#include <algorithm>
#include <numeric>

// ========== SORTING ==========

vector<Delivery> DataProcessor::sortByDeadline(vector<Delivery> deliveries)
{
    Sorting::mergeSort(deliveries, "deadline");
    return deliveries;
}

vector<Delivery> DataProcessor::sortByPriority(vector<Delivery> deliveries)
{
    Sorting::quickSort(deliveries, 0, (int)deliveries.size() - 1, "priority");
    return deliveries;
}

vector<Delivery> DataProcessor::sortByWeight(vector<Delivery> deliveries)
{
    Sorting::mergeSort(deliveries, "weight");
    return deliveries;
}

// ========== SEARCHING ==========

int DataProcessor::findDeliveryByDeadline(const vector<Delivery>& sorted, int deadline)
{
    int idx = Searching::binarySearchByDeadline(sorted, deadline);
    if (idx == -1)
        cout << "DataProcessor: No delivery with deadline=" << deadline << " found.\n";
    else
        cout << "DataProcessor: Found delivery at index " << idx
             << " (id=" << sorted[idx].id << ")\n";
    return idx;
}

int DataProcessor::findDeliveryById(const vector<Delivery>& sorted, int id)
{
    int idx = Searching::binarySearchById(sorted, id);
    if (idx == -1)
        cout << "DataProcessor: Delivery id=" << id << " not found.\n";
    else
        cout << "DataProcessor: Found delivery at index " << idx << "\n";
    return idx;
}

// ========== CLOSEST PAIR ==========

pair<pair<Location, Location>, double> DataProcessor::findClosestDeliveryPair(
    vector<Location> locations)
{
    return Searching::closestPair(locations);
}

// ========== ANALYTICS ==========

double DataProcessor::averageDeliveryWeight(const vector<Delivery>& deliveries) const
{
    if (deliveries.empty())
        return 0.0;
    double total = 0.0;
    for (const auto& d : deliveries)
        total += d.weight;
    return total / deliveries.size();
}

vector<Delivery> DataProcessor::filterByStatus(const vector<Delivery>& deliveries,
                                                const string& status) const
{
    vector<Delivery> result;
    for (const auto& d : deliveries)
        if (d.status == status)
            result.push_back(d);
    return result;
}

vector<Delivery> DataProcessor::filterOverdue(const vector<Delivery>& deliveries,
                                               int currentTime) const
{
    vector<Delivery> result;
    for (const auto& d : deliveries)
        if (d.isOverdue(currentTime))
            result.push_back(d);
    return result;
}

// Merge two already-sorted lists (merge step of MergeSort)
vector<Delivery> DataProcessor::mergeSortedLists(const vector<Delivery>& a,
                                                   const vector<Delivery>& b,
                                                   const string& criterion) const
{
    vector<Delivery> merged;
    merged.reserve(a.size() + b.size());
    int i = 0, j = 0;

    auto less = [&](const Delivery& x, const Delivery& y)
    {
        if (criterion == "deadline")  return x.deadline < y.deadline;
        if (criterion == "priority")  return x.priority > y.priority;
        return x.id < y.id;
    };

    while (i < (int)a.size() && j < (int)b.size())
    {
        if (less(a[i], b[j]))
            merged.push_back(a[i++]);
        else
            merged.push_back(b[j++]);
    }
    while (i < (int)a.size()) merged.push_back(a[i++]);
    while (j < (int)b.size()) merged.push_back(b[j++]);
    return merged;
}

// Top-K by priority using partial sort
vector<Delivery> DataProcessor::topKByPriority(vector<Delivery> deliveries, int k)
{
    if (k >= (int)deliveries.size())
    {
        Sorting::quickSort(deliveries, 0, (int)deliveries.size() - 1, "priority");
        return deliveries;
    }
    partial_sort(deliveries.begin(), deliveries.begin() + k, deliveries.end(),
                 [](const Delivery& a, const Delivery& b) { return a.priority > b.priority; });
    return vector<Delivery>(deliveries.begin(), deliveries.begin() + k);
}

// ========== REPORT ==========

void DataProcessor::displayReport(const vector<Delivery>& deliveries) const
{
    cout << "\n=== Data Processing Report ===\n";
    cout << "Total deliveries : " << deliveries.size() << "\n";
    cout << "Average weight   : " << averageDeliveryWeight(deliveries) << "\n";

    int pending = 0, assigned = 0, delivered = 0;
    for (const auto& d : deliveries)
    {
        if (d.status == "Pending")   pending++;
        if (d.status == "Assigned")  assigned++;
        if (d.status == "Delivered") delivered++;
    }
    cout << "Pending   : " << pending   << "\n";
    cout << "Assigned  : " << assigned  << "\n";
    cout << "Delivered : " << delivered << "\n";

    Sorting::displaySorted(deliveries, "Full Delivery List");
}
