#include "../../Headers/DataStructures/Graph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

Graph::Graph(int vertices, bool directed) : numVertices(vertices), isDirected(directed) {}

void Graph::addVertex(int v)
{
    if (adjList.find(v) == adjList.end())
        adjList[v] = vector<pair<int, double>>();
}

void Graph::addEdge(int u, int v, double weight)
{
    if (adjList.find(u) == adjList.end())
        adjList[u] = vector<pair<int, double>>();
    if (adjList.find(v) == adjList.end())
        adjList[v] = vector<pair<int, double>>();

    adjList[u].push_back({v, weight});

    if (!isDirected)
        adjList[v].push_back({u, weight});
}

void Graph::removeEdge(int u, int v)
{
    if (adjList.find(u) == adjList.end())
        return;

    auto& edges = adjList[u];
    edges.erase(remove_if(edges.begin(), edges.end(),
                         [v](const pair<int, double>& p) { return p.first == v; }),
               edges.end());

    if (!isDirected && adjList.find(v) != adjList.end())
    {
        auto& reverseEdges = adjList[v];
        reverseEdges.erase(remove_if(reverseEdges.begin(), reverseEdges.end(),
                                    [u](const pair<int, double>& p) { return p.first == u; }),
                          reverseEdges.end());
    }
}

void Graph::updateWeight(int u, int v, double newWeight)
{
    if (adjList.find(u) == adjList.end())
        return;

    for (auto& edge : adjList[u])
    {
        if (edge.first == v)
        {
            edge.second = newWeight;
            break;
        }
    }

    if (!isDirected && adjList.find(v) != adjList.end())
    {
        for (auto& edge : adjList[v])
        {
            if (edge.first == u)
            {
                edge.second = newWeight;
                break;
            }
        }
    }
}

void Graph::displayGraph() const
{
    cout << "\n=== Graph Adjacency List ===\n";
    for (const auto& pair : adjList)
    {
        cout << "Node " << pair.first << " -> ";
        for (const auto& edge : pair.second)
            cout << "(" << edge.first << ", w=" << edge.second << ") ";
        cout << "\n";
    }
}

bool Graph::containsVertex(int v) const
{
    return adjList.find(v) != adjList.end();
}

int Graph::getNumVertices() const
{
    return adjList.size();
}

vector<int> Graph::getAllVertices() const
{
    vector<int> vertices;
    for (const auto& pair : adjList)
        vertices.push_back(pair.first);
    return vertices;
}

int Graph::getNumEdges() const
{
    int edges = 0;
    for (const auto& pair : adjList)
        edges += pair.second.size();

    if (!isDirected)
        edges /= 2;

    return edges;
}

vector<pair<int, double>> Graph::getNeighbors(int vertex) const
{
    if (adjList.find(vertex) == adjList.end())
        return vector<pair<int, double>>();
    return adjList.at(vertex);
}

double Graph::getEdgeWeight(int u, int v) const
{
    if (adjList.find(u) == adjList.end())
        return -1;

    for (const auto& edge : adjList.at(u))
    {
        if (edge.first == v)
            return edge.second;
    }
    return -1;
}

void Graph::clear()
{
    adjList.clear();
    numVertices = 0;
}

// ========== TRAVERSALS ==========

vector<int> Graph::BFS(int start)
{
    vector<int> result;
    if (adjList.find(start) == adjList.end())
        return result;

    unordered_map<int, bool> visited;
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for (const auto& edge : adjList.at(node))
        {
            int neighbor = edge.first;
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return result;
}

void Graph::DFSUtil(int node, unordered_map<int, bool>& visited, vector<int>& result)
{
    visited[node] = true;
    result.push_back(node);

    if (adjList.find(node) != adjList.end())
    {
        for (const auto& edge : adjList.at(node))
        {
            int neighbor = edge.first;
            if (!visited[neighbor])
                DFSUtil(neighbor, visited, result);
        }
    }
}

vector<int> Graph::DFS(int start)
{
    vector<int> result;
    if (adjList.find(start) == adjList.end())
        return result;

    unordered_map<int, bool> visited;
    DFSUtil(start, visited, result);
    return result;
}

// ========== SHORTEST PATHS ==========

vector<double> Graph::Dijkstra(int source, vector<int>& parent)
{
    int maxId = source;
    for (const auto& p : adjList)
    {
        maxId = max(maxId, p.first);
        for (const auto& e : p.second)
            maxId = max(maxId, e.first);
    }
    int sz = maxId + 1;

    vector<double> dist(sz, numeric_limits<double>::max());
    parent.assign(sz, -1);

    dist[source] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    pq.push({0, source});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        if (adjList.find(u) != adjList.end())
        {
            for (const auto& edge : adjList.at(u))
            {
                int v = edge.first;
                double w = edge.second;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    return dist;
}

vector<double> Graph::BellmanFord(int source, vector<int>& parent)
{
    int maxId = source;
    for (const auto& p : adjList)
    {
        maxId = max(maxId, p.first);
        for (const auto& e : p.second)
            maxId = max(maxId, e.first);
    }
    int sz = maxId + 1;

    vector<double> dist(sz, numeric_limits<double>::max());
    parent.assign(sz, -1);

    dist[source] = 0;

    int V = adjList.size();

    for (int i = 0; i < V - 1; i++)
    {
        for (const auto& u_pair : adjList)
        {
            int u = u_pair.first;
            if (dist[u] == numeric_limits<double>::max())
                continue;

            for (const auto& edge : u_pair.second)
            {
                int v = edge.first;
                double w = edge.second;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    // Check for negative cycles
    for (const auto& u_pair : adjList)
    {
        int u = u_pair.first;
        if (dist[u] == numeric_limits<double>::max())
            continue;

        for (const auto& edge : u_pair.second)
        {
            int v = edge.first;
            double w = edge.second;

            if (dist[u] + w < dist[v])
            {
                cout << "Negative cycle detected!\n";
                return vector<double>();
            }
        }
    }

    return dist;
}

vector<int> Graph::reconstructPath(vector<int>& parent, int source, int destination)
{
    vector<int> path;
    int current = destination;

    while (current != -1)
    {
        path.push_back(current);
        if (current == source)
            break;
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    if (path.empty() || path[0] != source)
        return vector<int>();

    return path;
}

// ========== MST ==========

class UnionFind
{
public:
    vector<int> parent, rank;

    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);

        if (px == py)
            return false;

        if (rank[px] < rank[py])
            swap(px, py);

        parent[py] = px;
        if (rank[px] == rank[py])
            rank[px]++;

        return true;
    }
};

vector<tuple<int, int, double>> Graph::PrimMST()
{
    vector<tuple<int, int, double>> mst;

    if (adjList.empty())
        return mst;

    auto vertices = getAllVertices();
    int start = vertices[0];

    unordered_map<int, bool> inMST;
    priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>, greater<tuple<double, int, int>>> pq;

    inMST[start] = true;

    if (adjList.find(start) != adjList.end())
    {
        for (const auto& edge : adjList.at(start))
            pq.push({edge.second, start, edge.first});
    }

    while (!pq.empty())
    {
        auto [weight, u, v] = pq.top();
        pq.pop();

        if (inMST[v])
            continue;

        inMST[v] = true;
        mst.push_back({u, v, weight});

        if (adjList.find(v) != adjList.end())
        {
            for (const auto& edge : adjList.at(v))
            {
                if (!inMST[edge.first])
                    pq.push({edge.second, v, edge.first});
            }
        }
    }

    return mst;
}

vector<tuple<int, int, double>> Graph::KruskalMST()
{
    vector<tuple<int, int, double>> mst;
    vector<tuple<double, int, int>> edges;

    // Collect all edges
    for (const auto& u_pair : adjList)
    {
        int u = u_pair.first;
        for (const auto& edge : u_pair.second)
        {
            int v = edge.first;
            double w = edge.second;

            if (!isDirected && u > v)
                continue;

            edges.push_back({w, u, v});
        }
    }

    sort(edges.begin(), edges.end());

    int maxId = 0;
    for (const auto& p : adjList)
    {
        maxId = max(maxId, p.first);
        for (const auto& e : p.second)
            maxId = max(maxId, e.first);
    }
    UnionFind uf(maxId + 1);

    for (const auto& [weight, u, v] : edges)
    {
        if (uf.unite(u, v))
            mst.push_back({u, v, weight});
    }

    return mst;
}

// ========== DAG OPERATIONS ==========

bool Graph::hasCycleDFS(int node, unordered_map<int, int>& color)
{
    color[node] = 1;

    if (adjList.find(node) != adjList.end())
    {
        for (const auto& edge : adjList.at(node))
        {
            int neighbor = edge.first;

            if (color.find(neighbor) == color.end())
            {
                if (hasCycleDFS(neighbor, color))
                    return true;
            }
            else if (color[neighbor] == 1)
                return true;
        }
    }

    color[node] = 2;
    return false;
}

bool Graph::hasCycle()
{
    unordered_map<int, int> color;

    for (const auto& pair : adjList)
    {
        int node = pair.first;
        if (color.find(node) == color.end())
        {
            if (hasCycleDFS(node, color))
                return true;
        }
    }

    return false;
}

void Graph::topologicalSortUtil(int node, unordered_map<int, bool>& visited, stack<int>& st)
{
    visited[node] = true;

    if (adjList.find(node) != adjList.end())
    {
        for (const auto& edge : adjList.at(node))
        {
            int neighbor = edge.first;
            if (!visited[neighbor])
                topologicalSortUtil(neighbor, visited, st);
        }
    }

    st.push(node);
}

vector<int> Graph::TopologicalSort()
{
    vector<int> result;

    if (hasCycle())
    {
        cout << "Graph contains cycle! Topological sort not possible.\n";
        return result;
    }

    unordered_map<int, bool> visited;
    stack<int> st;

    for (const auto& pair : adjList)
    {
        int node = pair.first;
        if (!visited[node])
            topologicalSortUtil(node, visited, st);
    }

    while (!st.empty())
    {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

// ========== CONNECTIVITY ==========

bool Graph::hasPath(int u, int v)
{
    if (adjList.find(u) == adjList.end() || adjList.find(v) == adjList.end())
        return false;

    vector<int> path = BFS(u);
    return find(path.begin(), path.end(), v) != path.end();
}

vector<vector<int>> Graph::findConnectedComponents()
{
    vector<vector<int>> components;
    unordered_map<int, bool> visited;

    for (const auto& pair : adjList)
    {
        int node = pair.first;
        if (!visited[node])
        {
            vector<int> component = BFS(node);
            for (int n : component)
                visited[n] = true;
            components.push_back(component);
        }
    }

    return components;
}
