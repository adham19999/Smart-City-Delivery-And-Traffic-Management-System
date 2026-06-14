#ifndef CITYMAPMANAGER_H
#define CITYMAPMANAGER_H

#include "../DataStructures/Graph.h"
#include "../DataStructures/SegmentTree.h"
#include "../Models/Road.h"
#include "../Models/TrafficEvent.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Component 1: City Map Manager
// Wraps Graph; handles road network loading, traffic updates, pathfinding
class CityMapManager
{
private:
    Graph cityGraph;
    SegmentTree trafficDensity;
    vector<Road> roads;
    vector<TrafficEvent> trafficEvents;

public:
    CityMapManager(bool directed = true);

    // Road network management
    void addRoad(int from, int to, double weight);
    void removeRoad(int from, int to);
    void updateTrafficWeight(int from, int to, double newWeight);
    bool loadFromFile(const string& filename);
    bool loadTrafficUpdates(const string& filename);

    // Traffic monitoring
    void addTrafficEvent(const TrafficEvent& event);
    void applyTrafficEvents();
    void buildTrafficDensityTree(const vector<double>& densities);
    double getTrafficDensityRange(int left, int right);

    // Pathfinding
    vector<int> shortestPath(int from, int to);
    vector<int> shortestPathBellmanFord(int from, int to);
    double shortestDistance(int from, int to);
    bool pathExists(int from, int to);

    // Road analysis
    vector<vector<int>> getConnectedComponents();
    vector<int> suggestAlternativePath(int from, int to, int blockedFrom, int blockedTo);
    vector<tuple<int,int,double>> getMinimumSpanningTree();
    vector<int> getTopologicalOrder();

    // Traversal
    vector<int> exploreBFS(int start);
    vector<int> exploreDFS(int start);

    void displayMap() const;
    void displayRoads() const;
    int getRoadCount() const;

    // Expose graph for RouteOptimizer and other callers
    Graph& getGraph() { return cityGraph; }
};

#endif // CITYMAPMANAGER_H
