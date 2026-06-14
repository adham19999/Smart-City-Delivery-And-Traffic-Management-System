#include "../../Headers/Managers/SpatialQueryEngine.h"
#include <limits>
#include <cmath>

SpatialQueryEngine::SpatialQueryEngine(double cx, double cy, double w, double h, int capacity)
{
    locationTree = new QuadTree(cx, cy, w, h, capacity);
    cout << "SpatialQueryEngine: Initialized with bounds ("
         << cx << ", " << cy << ") size " << w*2 << "x" << h*2 << "\n";
}

SpatialQueryEngine::~SpatialQueryEngine()
{
    delete locationTree;
}

void SpatialQueryEngine::addLocation(const Location& loc)
{
    locationTree->insert(loc);
}

void SpatialQueryEngine::buildFromLocations(const vector<Location>& locations)
{
    for (const auto& loc : locations)
        locationTree->insert(loc);
    cout << "SpatialQueryEngine: Built from " << locations.size() << " locations.\n";
}

vector<Location> SpatialQueryEngine::findLocationsInRadius(const Location& center, double radius) const
{
    return locationTree->searchRadius(center, radius);
}

Location SpatialQueryEngine::findNearestLocation(const Location& point) const
{
    Location* nearest = locationTree->nearestNeighbor(point);
    if (nearest == nullptr)
    {
        cout << "SpatialQueryEngine: No locations in tree!\n";
        return Location();
    }
    return *nearest;
}

Vehicle SpatialQueryEngine::findNearestAvailableVehicle(const Location& pickup,
                                                         const vector<Vehicle>& vehicles,
                                                         const vector<Location>& vehicleLocs) const
{
    double minDist = numeric_limits<double>::max();
    Vehicle nearest;
    bool found = false;

    for (int i = 0; i < (int)vehicles.size(); i++)
    {
        if (!vehicles[i].available)
            continue;

        // Find the location matching this vehicle's current location
        for (const auto& loc : vehicleLocs)
        {
            if (loc.id == vehicles[i].currentLocation)
            {
                double d = pickup.distanceTo(loc);
                if (d < minDist)
                {
                    minDist = d;
                    nearest = vehicles[i];
                    found = true;
                }
                break;
            }
        }
    }

    if (found)
        cout << "SpatialQueryEngine: Nearest available vehicle is V"
             << nearest.id << " (dist=" << minDist << ")\n";
    else
        cout << "SpatialQueryEngine: No available vehicle found!\n";

    return nearest;
}

void SpatialQueryEngine::display() const
{
    locationTree->display();
}

int SpatialQueryEngine::totalLocations() const
{
    return locationTree->countPoints();
}
