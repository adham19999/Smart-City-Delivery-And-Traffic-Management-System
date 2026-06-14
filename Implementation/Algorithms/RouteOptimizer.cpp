#include "../../Headers/Algorithms/RouteOptimizer.h"
#include <algorithm>
#include <limits>

// ========== GREEDY HELPER ==========

double RouteOptimizer::getShortestDist(int from, int to, Graph& graph)
{
    vector<int> parent;
    vector<double> dist = graph.Dijkstra(from, parent);
    if (to < (int)dist.size())
        return dist[to];
    return numeric_limits<double>::max();
}

// ========== ACTIVITY SELECTION: maximize deliveries completed on time ==========

vector<Delivery> RouteOptimizer::selectOptimalDeliveries(vector<Delivery> deliveries,
                                                          int vehicleCapacity)
{
    // Greedy: sort by deadline, pick as many as fit within capacity
    sort(deliveries.begin(), deliveries.end(),
         [](const Delivery& a, const Delivery& b) { return a.deadline < b.deadline; });

    vector<Delivery> selected;
    double totalWeight = 0.0;

    cout << "\n=== Greedy Activity Selection ===\n";
    for (const auto& d : deliveries)
    {
        if (totalWeight + d.weight <= vehicleCapacity)
        {
            selected.push_back(d);
            totalWeight += d.weight;
            cout << "  Selected Delivery " << d.id << " (deadline=" << d.deadline
                 << ", weight=" << d.weight << ")\n";
        }
        else
        {
            cout << "  Skipped Delivery " << d.id << " (would exceed capacity)\n";
        }
    }

    cout << "Selected " << selected.size() << "/" << deliveries.size()
         << " deliveries, total weight=" << totalWeight << "\n";
    return selected;
}

// ========== NEAREST NEIGHBOR TSP APPROXIMATION ==========

vector<int> RouteOptimizer::nearestNeighborRoute(int startLocation,
                                                  const vector<int>& destinations,
                                                  Graph& graph)
{
    vector<int> remaining = destinations;
    vector<int> route;
    route.push_back(startLocation);
    int current = startLocation;

    cout << "\n=== Greedy Nearest-Neighbor Route ===\n";
    cout << "Start: " << startLocation << "\n";

    while (!remaining.empty())
    {
        double minDist = numeric_limits<double>::max();
        int nearest = -1;
        int nearestIdx = -1;

        for (int i = 0; i < (int)remaining.size(); i++)
        {
            double d = getShortestDist(current, remaining[i], graph);
            if (d < minDist)
            {
                minDist = d;
                nearest = remaining[i];
                nearestIdx = i;
            }
        }

        if (nearest == -1)
            break;

        route.push_back(nearest);
        cout << "  -> Location " << nearest << " (dist=" << minDist << ")\n";
        remaining.erase(remaining.begin() + nearestIdx);
        current = nearest;
    }

    cout << "Route length: " << route.size() << " stops\n";
    return route;
}

// ========== FRACTIONAL KNAPSACK ==========

vector<Delivery> RouteOptimizer::fractionalKnapsack(vector<Delivery> deliveries,
                                                      double weightLimit)
{
    // Greedy: sort by priority/weight ratio descending
    sort(deliveries.begin(), deliveries.end(),
         [](const Delivery& a, const Delivery& b)
         {
             double ratioA = (double)a.priority / (a.weight > 0 ? a.weight : 1);
             double ratioB = (double)b.priority / (b.weight > 0 ? b.weight : 1);
             return ratioA > ratioB;
         });

    vector<Delivery> loaded;
    double remaining = weightLimit;

    cout << "\n=== Fractional Knapsack (weight limit=" << weightLimit << ") ===\n";
    for (auto& d : deliveries)
    {
        if (remaining <= 0.0)
            break;
        if (d.weight <= remaining)
        {
            loaded.push_back(d);
            remaining -= d.weight;
            cout << "  Loaded Delivery " << d.id << " (weight=" << d.weight << ")\n";
        }
    }
    cout << "Loaded " << loaded.size() << " deliveries, remaining capacity=" << remaining << "\n";
    return loaded;
}

// ========== GREEDY VEHICLE ASSIGNMENT ==========

vector<pair<int, vector<Delivery>>> RouteOptimizer::assignVehiclesToDeliveries(
    vector<Vehicle>& vehicles,
    vector<Delivery>& deliveries)
{
    // Sort deliveries by priority descending
    sort(deliveries.begin(), deliveries.end(),
         [](const Delivery& a, const Delivery& b) { return a.priority > b.priority; });

    vector<pair<int, vector<Delivery>>> assignments;
    vector<double> vehicleLoad(vehicles.size(), 0.0);

    for (auto& vehicle : vehicles)
        assignments.push_back({vehicle.id, {}});

    cout << "\n=== Greedy Vehicle Assignment ===\n";
    for (const auto& d : deliveries)
    {
        // Assign to the vehicle with most remaining capacity
        int bestVehicleIdx = -1;
        double bestRemaining = -1.0;

        for (int i = 0; i < (int)vehicles.size(); i++)
        {
            if (!vehicles[i].available)
                continue;
            double remaining = vehicles[i].capacity - vehicleLoad[i];
            if (remaining >= d.weight && remaining > bestRemaining)
            {
                bestRemaining = remaining;
                bestVehicleIdx = i;
            }
        }

        if (bestVehicleIdx >= 0)
        {
            assignments[bestVehicleIdx].second.push_back(d);
            vehicleLoad[bestVehicleIdx] += d.weight;
            cout << "  Delivery " << d.id << " -> Vehicle " << vehicles[bestVehicleIdx].id << "\n";
        }
        else
        {
            cout << "  Delivery " << d.id << " -> No available vehicle!\n";
        }
    }

    return assignments;
}
