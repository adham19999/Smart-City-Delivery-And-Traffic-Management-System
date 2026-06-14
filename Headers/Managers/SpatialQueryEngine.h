#ifndef SPATIALQUERYENGINE_H
#define SPATIALQUERYENGINE_H

#include "../DataStructures/QuadTree.h"
#include "../Models/Location.h"
#include "../Models/Vehicle.h"
#include <vector>
#include <iostream>
using namespace std;

// Component 3: Spatial Query Engine (Tree-based)
// Wraps QuadTree for efficient nearest-neighbor and radius queries
class SpatialQueryEngine
{
private:
    QuadTree* locationTree;

public:
    SpatialQueryEngine(double centerX, double centerY, double width, double height, int capacity = 4);
    ~SpatialQueryEngine();

    void addLocation(const Location& loc);
    void buildFromLocations(const vector<Location>& locations);

    vector<Location> findLocationsInRadius(const Location& center, double radius) const;
    Location findNearestLocation(const Location& point) const;

    Vehicle findNearestAvailableVehicle(const Location& pickup,
                                        const vector<Vehicle>& vehicles,
                                        const vector<Location>& vehicleLocs) const;

    void display() const;
    int totalLocations() const;
};

#endif // SPATIALQUERYENGINE_H
