#include "../../Headers/Managers/CityMapManager.h"
#include <fstream>
#include <sstream>

CityMapManager::CityMapManager(bool directed) : cityGraph(0, directed) {}

// ========== ROAD MANAGEMENT ==========

void CityMapManager::addRoad(int from, int to, double weight)
{
    cityGraph.addEdge(from, to, weight);
    roads.push_back(Road(from, to, weight));
    cout << "CityMapManager: Road " << from << " -> " << to << " (weight=" << weight << ") added.\n";
}

void CityMapManager::removeRoad(int from, int to)
{
    cityGraph.removeEdge(from, to);
    roads.erase(
        remove_if(roads.begin(), roads.end(),
                  [from, to](const Road& r) { return r.from == from && r.to == to; }),
        roads.end());
    cout << "CityMapManager: Road " << from << " -> " << to << " removed.\n";
}

void CityMapManager::updateTrafficWeight(int from, int to, double newWeight)
{
    cityGraph.updateWeight(from, to, newWeight);
    for (auto& r : roads)
    {
        if (r.from == from && r.to == to)
        {
            r.weight = newWeight;
            break;
        }
    }
    cout << "CityMapManager: Road " << from << " -> " << to << " weight -> " << newWeight << "\n";
}

bool CityMapManager::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "CityMapManager: Cannot open " << filename << "\n";
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        istringstream ss(line);
        int from, to;
        double weight;
        if (ss >> from >> to >> weight)
        {
            addRoad(from, to, weight);
            count++;
        }
    }
    file.close();
    cout << "CityMapManager: Loaded " << count << " roads from " << filename << "\n";
    return true;
}

bool CityMapManager::loadTrafficUpdates(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "CityMapManager: Cannot open " << filename << "\n";
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        istringstream ss(line);
        int id, roadId, severity;
        double density;
        string timestamp;
        if (ss >> id >> roadId >> severity >> density >> timestamp)
        {
            TrafficEvent event(id, roadId, severity, density, timestamp);
            addTrafficEvent(event);
            count++;
        }
    }
    file.close();
    cout << "CityMapManager: Loaded " << count << " traffic events from " << filename << "\n";
    return true;
}

// ========== TRAFFIC MONITORING ==========

void CityMapManager::addTrafficEvent(const TrafficEvent& event)
{
    trafficEvents.push_back(event);
    cout << "CityMapManager: Traffic event " << event.id
         << " (road=" << event.roadId << ", severity=" << event.severity << ") added.\n";
}

void CityMapManager::applyTrafficEvents()
{
    cout << "\n=== Applying Traffic Events ===\n";
    for (const auto& event : trafficEvents)
    {
        if (event.isHighSeverity())
        {
            // Find the road and double its weight (simulating congestion)
            for (const auto& r : roads)
            {
                if (r.from == event.roadId || r.to == event.roadId)
                {
                    double newWeight = r.weight * (1.0 + event.density);
                    updateTrafficWeight(r.from, r.to, newWeight);
                }
            }
        }
    }
}

void CityMapManager::buildTrafficDensityTree(const vector<double>& densities)
{
    trafficDensity.build(densities);
}

double CityMapManager::getTrafficDensityRange(int left, int right)
{
    return trafficDensity.rangeMax(left, right);
}

// ========== PATHFINDING ==========

vector<int> CityMapManager::shortestPath(int from, int to)
{
    vector<int> parent;
    cityGraph.Dijkstra(from, parent);

    if ((int)parent.size() <= to || (parent[to] == -1 && to != from))
    {
        cout << "CityMapManager: No path from " << from << " to " << to << "\n";
        return {};
    }

    vector<int> path = cityGraph.reconstructPath(parent, from, to);
    if (path.empty())
        cout << "CityMapManager: No path from " << from << " to " << to << "\n";
    else
    {
        cout << "CityMapManager: Shortest path " << from << " -> " << to << ": ";
        for (int n : path) cout << n << " ";
        cout << "\n";
    }
    return path;
}

vector<int> CityMapManager::shortestPathBellmanFord(int from, int to)
{
    vector<int> parent;
    vector<double> dist = cityGraph.BellmanFord(from, parent);

    if (dist.empty())
        return {};

    vector<int> path = cityGraph.reconstructPath(parent, from, to);
    if (path.empty())
        cout << "CityMapManager: No path (BellmanFord) from " << from << " to " << to << "\n";
    else
    {
        cout << "CityMapManager: BellmanFord path " << from << " -> " << to << ": ";
        for (int n : path) cout << n << " ";
        cout << "\n";
    }
    return path;
}

double CityMapManager::shortestDistance(int from, int to)
{
    vector<int> parent;
    vector<double> dist = cityGraph.Dijkstra(from, parent);

    if (to < (int)dist.size())
        return dist[to];
    return -1.0;
}

bool CityMapManager::pathExists(int from, int to)
{
    return cityGraph.hasPath(from, to);
}

// ========== ROAD ANALYSIS ==========

vector<vector<int>> CityMapManager::getConnectedComponents()
{
    return cityGraph.findConnectedComponents();
}

vector<int> CityMapManager::suggestAlternativePath(int from, int to, int blockedFrom, int blockedTo)
{
    cityGraph.removeEdge(blockedFrom, blockedTo);
    vector<int> path = shortestPath(from, to);
    cityGraph.addEdge(blockedFrom, blockedTo,
                      cityGraph.getEdgeWeight(blockedTo, blockedFrom));
    return path;
}

vector<tuple<int,int,double>> CityMapManager::getMinimumSpanningTree()
{
    return cityGraph.KruskalMST();
}

vector<int> CityMapManager::getTopologicalOrder()
{
    return cityGraph.TopologicalSort();
}

vector<int> CityMapManager::exploreBFS(int start)
{
    return cityGraph.BFS(start);
}

vector<int> CityMapManager::exploreDFS(int start)
{
    return cityGraph.DFS(start);
}

// ========== DISPLAY ==========

void CityMapManager::displayMap() const
{
    cityGraph.displayGraph();
}

void CityMapManager::displayRoads() const
{
    cout << "\n=== City Roads ===\n";
    for (const auto& r : roads)
        r.display();
}

int CityMapManager::getRoadCount() const
{
    return (int)roads.size();
}
