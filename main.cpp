#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Models
#include "Headers/Models/Location.h"
#include "Headers/Models/Vehicle.h"
#include "Headers/Models/Customer.h"
#include "Headers/Models/Delivery.h"
#include "Headers/Models/Road.h"
#include "Headers/Models/TrafficEvent.h"

// Data Structures
#include "Headers/DataStructures/Graph.h"
#include "Headers/DataStructures/PriorityQueue.h"
#include "Headers/DataStructures/BST.h"
#include "Headers/DataStructures/SegmentTree.h"
#include "Headers/DataStructures/QuadTree.h"
#include "Headers/DataStructures/HashTable.h"

// Algorithms
#include "Headers/Algorithms/Sorting.h"
#include "Headers/Algorithms/Searching.h"
#include "Headers/Algorithms/RouteOptimizer.h"

// Managers
#include "Headers/Managers/EntityManager.h"
#include "Headers/Managers/CityMapManager.h"
#include "Headers/Managers/DeliveryScheduler.h"
#include "Headers/Managers/SpatialQueryEngine.h"
#include "Headers/Managers/DataProcessor.h"

using namespace std;

// ──────────────────────────────────────────────
// File loaders
// ──────────────────────────────────────────────

void loadLocations(EntityManager& em, SpatialQueryEngine& spatial,
                   const string& filename)
{
    ifstream f(filename);
    if (!f.is_open()) { cout << "Cannot open " << filename << "\n"; return; }
    string line;
    while (getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;
        istringstream ss(line);
        int id; string name; double x, y; string type;
        if (ss >> id >> name >> x >> y >> type)
        {
            Location loc(id, name, x, y, type);
            em.addLocation(loc);
            spatial.addLocation(loc);
        }
    }
}

void loadVehicles(EntityManager& em, const string& filename)
{
    ifstream f(filename);
    if (!f.is_open()) { cout << "Cannot open " << filename << "\n"; return; }
    string line;
    while (getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;
        istringstream ss(line);
        int id, loc, avail; double cap, speed;
        if (ss >> id >> cap >> speed >> loc >> avail)
        {
            Vehicle v(id, cap, speed, loc, (avail == 1));
            em.addVehicle(v);
        }
    }
}

void loadCustomers(EntityManager& em, const string& filename)
{
    ifstream f(filename);
    if (!f.is_open()) { cout << "Cannot open " << filename << "\n"; return; }
    string line;
    while (getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;
        istringstream ss(line);
        int id; string name, address, phone;
        if (ss >> id >> name >> address >> phone)
        {
            Customer c(id, name, address, phone);
            em.addCustomer(c);
        }
    }
}

void loadDeliveries(EntityManager& em, DeliveryScheduler& sched,
                    const string& filename)
{
    ifstream f(filename);
    if (!f.is_open()) { cout << "Cannot open " << filename << "\n"; return; }
    string line;
    while (getline(f, line))
    {
        if (line.empty() || line[0] == '#') continue;
        istringstream ss(line);
        int id, cust, pickup, dropoff, prio, deadline; double weight;
        if (ss >> id >> cust >> pickup >> dropoff >> prio >> deadline >> weight)
        {
            Delivery d(id, cust, pickup, dropoff, prio, deadline, weight);
            em.addDelivery(d);
            sched.scheduleDelivery(d);
        }
    }
}

// ──────────────────────────────────────────────
// Section separators
// ──────────────────────────────────────────────
void section(const string& title)
{
    cout << "\n";
    cout << "==================================================\n";
    cout << title << "\n";
    cout << "==================================================\n";
}

// ──────────────────────────────────────────────
// MAIN
// ──────────────────────────────────────────────
int main()
{
    cout << "======================================================\n";
    cout << " Smart City Delivery & Traffic Management System\n";
    cout << "======================================================\n";

    // ── 1. INITIALISE COMPONENTS ──────────────────────────────
    section("1. Initialising System Components");

    EntityManager       entityMgr;
    CityMapManager      cityMap(true);                       // directed graph
    DeliveryScheduler   scheduler;
    SpatialQueryEngine  spatial(55.0, 50.0, 55.0, 50.0, 4); // bounds cover all locations
    DataProcessor       processor;

    // ── 2. LOAD DATA FROM FILES ───────────────────────────────
    section("2. Loading Data from Files");

    cityMap.loadFromFile("Data/city_map.txt");
    loadLocations(entityMgr, spatial, "Data/locations.txt");
    loadVehicles(entityMgr, "Data/vehicles.txt");
    loadCustomers(entityMgr, "Data/customers.txt");
    loadDeliveries(entityMgr, scheduler, "Data/deliveries.txt");

    // ── 3. ENTITY MANAGER (Hash Table) ────────────────────────
    section("3. Hash-Based Entity Manager");

    entityMgr.displayStats();

    cout << "\n[Fast O(1) Lookup]\n";
    Location* hub = entityMgr.getLocation(1);
    if (hub) { cout << "Found: "; hub->display(); }

    Vehicle* v2 = entityMgr.getVehicle(2);
    if (v2) { cout << "Found: "; v2->display(); }

    // ── 4. CITY MAP — GRAPH ALGORITHMS ────────────────────────
    section("4. City Road Network — Graph Algorithms");

    cityMap.displayMap();

    cout << "\n[Dijkstra: Shortest path 1 -> 10]\n";
    vector<int> path = cityMap.shortestPath(1, 10);

    cout << "\n[Bellman-Ford: Shortest path 2 -> 9]\n";
    vector<int> pathBF = cityMap.shortestPathBellmanFord(2, 9);

    cout << "\n[BFS from node 1]\n";
    vector<int> bfsResult = cityMap.exploreBFS(1);
    cout << "BFS order: ";
    for (int n : bfsResult) cout << n << " ";
    cout << "\n";

    cout << "\n[DFS from node 1]\n";
    vector<int> dfsResult = cityMap.exploreDFS(1);
    cout << "DFS order: ";
    for (int n : dfsResult) cout << n << " ";
    cout << "\n";

    cout << "\n[Kruskal MST]\n";
    auto mst = cityMap.getMinimumSpanningTree();
    cout << "MST edges (" << mst.size() << "):\n";
    for (auto& [u, v, w] : mst)
        cout << "  " << u << " -- " << v << "  (w=" << w << ")\n";

    cout << "\n[Connected Components]\n";
    auto comps = cityMap.getConnectedComponents();
    cout << comps.size() << " component(s)\n";

    // ── 5. SEGMENT TREE — TRAFFIC DENSITY ─────────────────────
    section("5. Segment Tree — Traffic Density Range Queries");

    vector<double> densities = {0.3, 0.5, 0.8, 0.2, 0.7, 0.4, 0.9, 0.1, 0.6, 0.3};
    cityMap.buildTrafficDensityTree(densities);
    cout << "\nTotal density roads [0-4]: " << cityMap.getTrafficDensityRange(0, 4) << "\n";
    cout << "Max density roads  [2-7]: " << cityMap.getTrafficDensityRange(2, 7) << "\n";

    // ── 6. DELIVERY SCHEDULER (Priority Queue + BST) ──────────
    section("6. Delivery Scheduler — Priority Queue + BST");

    scheduler.display();

    cout << "\n[Processing top-3 urgent deliveries]\n";
    for (int i = 0; i < 3; i++)
    {
        if (scheduler.hasPendingDeliveries())
        {
            Delivery next = scheduler.getNextUrgentDelivery();
            cout << "Processing: ";
            next.display();
            entityMgr.updateDeliveryStatus(next.id, "In-Transit");
        }
    }

    cout << "\n[Deadline-sorted remaining deliveries]\n";
    auto sorted = scheduler.getDeadlineSortedDeliveries();
    for (const auto& d : sorted) d.display();

    // ── 7. SPATIAL QUERY ENGINE (QuadTree) ────────────────────
    section("7. Spatial Query Engine — QuadTree");

    spatial.display();

    Location searchCenter(0, "SearchPoint", 75.0, 50.0, "Virtual");
    cout << "\n[Locations within radius 30 of (75, 50)]\n";
    auto nearby = spatial.findLocationsInRadius(searchCenter, 30.0);
    cout << "Found " << nearby.size() << " locations\n";

    cout << "\n[Nearest location to (75, 50)]\n";
    Location nearest = spatial.findNearestLocation(searchCenter);
    nearest.display();

    cout << "\n[Nearest available vehicle to location 6]\n";
    Location* loc6 = entityMgr.getLocation(6);
    if (loc6)
    {
        vector<Vehicle>  vehicles = entityMgr.getAllVehicles();
        vector<Location> locs     = entityMgr.getAllLocations();
        Vehicle best = spatial.findNearestAvailableVehicle(*loc6, vehicles, locs);
        if (best.id > 0) best.display();
    }

    // ── 8. DATA PROCESSOR (Sorting + Searching) ───────────────
    section("8. Data Processor — Divide & Conquer");

    vector<Delivery> allDeliveries = entityMgr.getAllDeliveries();

    cout << "\n[MergeSort by deadline]\n";
    auto byDeadline = processor.sortByDeadline(allDeliveries);
    Sorting::displaySorted(byDeadline, "Sorted by Deadline");

    cout << "\n[QuickSort by priority]\n";
    auto byPriority = processor.sortByPriority(allDeliveries);
    Sorting::displaySorted(byPriority, "Sorted by Priority");

    cout << "\n[Binary Search: delivery with deadline=100]\n";
    processor.findDeliveryByDeadline(byDeadline, 100);

    cout << "\n[Closest Pair of Delivery Locations]\n";
    vector<Location> delivLocs;
    for (const auto& d : allDeliveries)
    {
        Location* l = entityMgr.getLocation(d.dropoffLocation);
        if (l) delivLocs.push_back(*l);
    }
    if (delivLocs.size() >= 2)
        processor.findClosestDeliveryPair(delivLocs);

    processor.displayReport(allDeliveries);

    // ── 9. ROUTE OPTIMIZER (Greedy) ───────────────────────────
    section("9. Route Optimizer — Greedy Algorithms");

    cout << "\n[Activity Selection: optimal delivery batch for vehicle capacity=50]\n";
    auto selected = RouteOptimizer::selectOptimalDeliveries(allDeliveries, 50);

    cout << "\n[Nearest-Neighbor Route from location 1]\n";
    vector<int> destinations = {6, 7, 8, 9, 10};
    // Use a local demo graph for the route optimizer (same topology as city_map.txt)
    Graph demoGraph(10, true);
    demoGraph.addEdge(1,2,5); demoGraph.addEdge(1,3,10); demoGraph.addEdge(2,3,3);
    demoGraph.addEdge(2,4,8); demoGraph.addEdge(3,5,6);  demoGraph.addEdge(4,5,2);
    demoGraph.addEdge(4,6,7); demoGraph.addEdge(5,6,4);  demoGraph.addEdge(5,7,9);
    demoGraph.addEdge(6,7,1); demoGraph.addEdge(6,8,5);  demoGraph.addEdge(7,8,3);
    demoGraph.addEdge(7,9,6); demoGraph.addEdge(8,9,2);  demoGraph.addEdge(8,10,8);
    demoGraph.addEdge(9,10,4);
    vector<int> route = RouteOptimizer::nearestNeighborRoute(1, destinations, demoGraph);
    cout << "Optimised route: ";
    for (int n : route) cout << n << " ";
    cout << "\n";

    cout << "\n[Fractional Knapsack: weight limit=40]\n";
    RouteOptimizer::fractionalKnapsack(allDeliveries, 40.0);

    cout << "\n[Greedy Vehicle Assignment]\n";
    vector<Vehicle> vList = entityMgr.getAvailableVehicles();
    RouteOptimizer::assignVehiclesToDeliveries(vList, allDeliveries);

    // ── 10. TRAFFIC UPDATE SCENARIO ───────────────────────────
    section("10. Rush-Hour Traffic Update Scenario");

    cityMap.loadTrafficUpdates("Data/traffic_updates.txt");
    cout << "\n[Applying high-severity traffic events to road weights]\n";
    cityMap.applyTrafficEvents();

    cout << "\n[Recalculating route 1 -> 10 after traffic update]\n";
    vector<int> newPath = cityMap.shortestPath(1, 10);

    // ── 11. ANALYTICS ─────────────────────────────────────────
    section("11. Analytics & Reporting");

    cout << "\n[Top-3 deliveries by priority]\n";
    auto top3 = processor.topKByPriority(allDeliveries, 3);
    for (const auto& d : top3) d.display();

    cout << "\n[Average delivery weight]: "
         << processor.averageDeliveryWeight(allDeliveries) << "\n";

    cout << "\n[Overdue deliveries at time=95]\n";
    auto overdue = scheduler.getOverdueDeliveries(95);
    if (overdue.empty())
        cout << "No overdue deliveries at time=95\n";
    else
        for (const auto& d : overdue) d.display();

    // ── SUMMARY ───────────────────────────────────────────────
    section("System Summary");

    entityMgr.displayStats();
    cout << "\nCity roads loaded  : " << cityMap.getRoadCount() << "\n";
    cout << "Pending deliveries : " << scheduler.pendingCount() << "\n";
    cout << "Spatial locations  : " << spatial.totalLocations() << "\n";

    cout << "\n======================================================\n";
    cout << " All systems operational - Demo complete\n";
    cout << "======================================================\n";
    return 0;
}
