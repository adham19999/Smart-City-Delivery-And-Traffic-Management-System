#include "../../Headers/Algorithms/Searching.h"
#include <algorithm>
#include <cmath>
#include <limits>

// ========== DISTANCE HELPER ==========

double Searching::dist(const Location& a, const Location& b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// ========== BINARY SEARCH ==========

int Searching::binarySearchByDeadline(const vector<Delivery>& sorted, int deadline)
{
    int low = 0, high = (int)sorted.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (sorted[mid].deadline == deadline)
            return mid;
        else if (sorted[mid].deadline < deadline)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int Searching::binarySearchById(const vector<Delivery>& sorted, int id)
{
    int low = 0, high = (int)sorted.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (sorted[mid].id == id)
            return mid;
        else if (sorted[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int Searching::linearSearchById(const vector<Delivery>& deliveries, int id)
{
    for (int i = 0; i < (int)deliveries.size(); i++)
    {
        if (deliveries[i].id == id)
            return i;
    }
    return -1;
}

// ========== CLOSEST PAIR (Divide & Conquer) O(n log n) ==========

pair<pair<Location, Location>, double> Searching::closestPair(vector<Location>& locations)
{
    if (locations.size() < 2)
    {
        cout << "Closest Pair: Need at least 2 locations!\n";
        return {{Location(), Location()}, -1.0};
    }

    // Sort by x-coordinate
    sort(locations.begin(), locations.end(),
         [](const Location& a, const Location& b) { return a.x < b.x; });

    auto result = closestPairRec(locations, 0, (int)locations.size() - 1);

    cout << "Closest Pair: Location " << result.first.first.id
         << " and Location " << result.first.second.id
         << " (distance=" << result.second << ")\n";

    return result;
}

pair<pair<Location, Location>, double> Searching::closestPairRec(
    vector<Location>& pts, int left, int right)
{
    // Base cases
    if (right - left + 1 <= 3)
    {
        double minD = numeric_limits<double>::max();
        pair<Location, Location> best = {pts[left], pts[left + 1]};
        minD = dist(pts[left], pts[left + 1]);

        for (int i = left; i <= right; i++)
        {
            for (int j = i + 1; j <= right; j++)
            {
                double d = dist(pts[i], pts[j]);
                if (d < minD)
                {
                    minD = d;
                    best = {pts[i], pts[j]};
                }
            }
        }
        return {best, minD};
    }

    int mid = left + (right - left) / 2;
    double midX = pts[mid].x;

    auto leftResult  = closestPairRec(pts, left, mid);
    auto rightResult = closestPairRec(pts, mid + 1, right);

    double d = min(leftResult.second, rightResult.second);
    auto best = (leftResult.second <= rightResult.second) ? leftResult : rightResult;

    // Build strip of points within distance d of the mid-line
    vector<Location> strip;
    for (int i = left; i <= right; i++)
    {
        if (abs(pts[i].x - midX) < d)
            strip.push_back(pts[i]);
    }

    // Sort strip by y and check cross-pair distances
    sort(strip.begin(), strip.end(),
         [](const Location& a, const Location& b) { return a.y < b.y; });

    auto stripResult = stripClosest(strip, d);
    if (stripResult.second < best.second)
        return stripResult;

    return best;
}

pair<pair<Location, Location>, double> Searching::stripClosest(
    vector<Location>& strip, double d)
{
    if (strip.empty())
        return {{Location(), Location()}, d};

    double minD = d;
    pair<Location, Location> best = {strip[0], strip[0]};

    for (int i = 0; i < (int)strip.size(); i++)
    {
        for (int j = i + 1; j < (int)strip.size() && (strip[j].y - strip[i].y) < minD; j++)
        {
            double distance = dist(strip[i], strip[j]);
            if (distance < minD)
            {
                minD = distance;
                best = {strip[i], strip[j]};
            }
        }
    }

    return {best, minD};
}
