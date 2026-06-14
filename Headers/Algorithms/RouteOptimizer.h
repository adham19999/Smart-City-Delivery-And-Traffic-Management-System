#ifndef ROUTEOPTIMIZER_H
#define ROUTEOPTIMIZER_H

#include "../Models/Delivery.h"
#include "../Models/Vehicle.h"
#include "../Models/Location.h"
#include "../DataStructures/Graph.h"
#include <vector>
#include <iostream>
using namespace std;

// Greedy route optimization component (PDF Component 5)
class RouteOptimizer
{
public:
    // Activity selection: pick deliveries that maximize profit/time
    // Sorts by deadline and greedily assigns non-overlapping time slots
    static vector<Delivery> selectOptimalDeliveries(vector<Delivery> deliveries, int vehicleCapacity);

    // Greedy nearest-neighbor TSP approximation
    // Given a vehicle start and a set of delivery locations, return visit order
    static vector<int> nearestNeighborRoute(int startLocation,
                                            const vector<int>& destinations,
                                            Graph& graph);

    // Fractional knapsack: maximize value of deliveries loaded within weight limit
    static vector<Delivery> fractionalKnapsack(vector<Delivery> deliveries, double weightLimit);

    // Assign vehicles to delivery clusters (greedy load balancing)
    static vector<pair<int, vector<Delivery>>> assignVehiclesToDeliveries(
        vector<Vehicle>& vehicles,
        vector<Delivery>& deliveries);

private:
    static double getShortestDist(int from, int to, Graph& graph);
};

#endif // ROUTEOPTIMIZER_H
