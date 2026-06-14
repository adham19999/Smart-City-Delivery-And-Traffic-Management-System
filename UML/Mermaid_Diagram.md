# Smart City UML - Mermaid Diagram

## Class Diagram

```mermaid
---
id: 077b564f-088b-44c7-9556-d42c144086a3
---
classDiagram
    direction TB

    %% ========== DATA STRUCTURES ==========
    class Graph {
        -adjList: unordered_map~int, vector~pair~int,double~~~
        +addEdge(u, v, weight)
        +removeEdge(u, v)
        +updateWeight(u, v, weight)
        +BFS(start) vector~int~
        +DFS(start) vector~int~
        +Dijkstra(start) vector~double~
        +BellmanFord(start) vector~double~
        +PrimMST() vector~pair~int,int~~
        +KruskalMST() vector~pair~int,int~~
        +TopologicalSort() vector~int~
    }

    class QuadTree {
        -root: QuadTreeNode*
        +insert(point, data)
        +nearestNeighbor(point) pair~point, data~
        +searchRadius(center, radius) vector~data~
    }

    class BST {
        -root: BSTNode*
        +insert(value)
        +search(value) BSTNode*
        +remove(value)
        +inorder() vector~int~
    }

    class SegmentTree {
        -tree: vector~int~
        +build(arr)
        +query(l, r) int
        +update(index, value)
    }

    class DeliveryPriorityQueue {
        -heap: priority_queue~Delivery~
        +insert(delivery)
        +extractMax() Delivery
        +updatePriority(deliveryId, priority)
    }

    %% ========== MODELS ==========
    class Location {
        -id: int
        -name: string
        -x: double
        -y: double
        -type: string
    }

    class Vehicle {
        -id: int
        -capacity: double
        -speed: double
        -currentLocation: int
        -available: bool
    }

    class Customer {
        -id: int
        -name: string
        -address: string
        -phone: string
    }

    class Delivery {
        -id: int
        -customerId: int
        -pickupLocation: int
        -dropoffLocation: int
        -deadline: datetime
        -priority: int
        -status: string
    }

    class Road {
        -from: int
        -to: int
        -weight: double
    }

    class TrafficEvent {
        -id: int
        -roadId: int
        -severity: int
        -density: double
        -timestamp: datetime
    }

    %% ========== MANAGERS & ALGORITHMS ==========
    class EntityManager {
        -locations: unordered_map~int, Location~
        -vehicles: unordered_map~int, Vehicle~
        -customers: unordered_map~int, Customer~
        -deliveries: unordered_map~int, Delivery~
        +addLocation(location)
        +addVehicle(vehicle)
        +addCustomer(customer)
        +addDelivery(delivery)
        +getLocation(id) Location
        +getVehicle(id) Vehicle
        +getCustomer(id) Customer
        +getDelivery(id) Delivery
    }

    class CityMapManager {
        -graph: Graph
        +loadCity(filepath)
        +updateTraffic(trafficEvent)
        +findShortestPath(from, to) vector~int~
    }

    class SpatialQueryEngine {
        -quadTree: QuadTree
        +findNearestVehicle(location) Vehicle
        +findLocationsInRadius(center, radius) vector~Location~
    }

    class DeliveryScheduler {
        -pq: DeliveryPriorityQueue
        +scheduleDelivery(delivery)
        +updatePriority(deliveryId, priority)
        +assignVehicle(delivery) Vehicle
    }

    class DataProcessor {
        +mergeSort(arr) vector~int~
        +quickSort(arr) vector~int~
        +binarySearch(arr, target) int
        +closestPair(points) pair~Point, Point~
    }

    class RouteOptimizer {
        +optimizeRoute(deliveries, vehicle) vector~int~
        +assignVehicles(deliveries, vehicles) map~int,vector~int~~
        +selectDeliveries(deliveries, capacity) vector~int~
        +fractionalKnapsack(items, capacity) double
    }

    %% ========== RELATIONSHIPS ==========
    
    %% EntityManager relationships
    EntityManager --> Location: stores
    EntityManager --> Vehicle: stores
    EntityManager --> Customer: stores
    EntityManager --> Delivery: stores

    %% CityMapManager relationships
    CityMapManager --> Graph: contains
    CityMapManager --> Road: builds from
    CityMapManager --> TrafficEvent: receives updates

    %% DeliveryScheduler relationships
    DeliveryScheduler --> DeliveryPriorityQueue: uses
    DeliveryScheduler --> Delivery: manages

    %% SpatialQueryEngine relationships
    SpatialQueryEngine --> QuadTree: contains
    SpatialQueryEngine --> Location: queries

    %% Integration relationships
    EntityManager --> DeliveryScheduler: provides data
    EntityManager --> RouteOptimizer: provides entities
    DeliveryScheduler --> RouteOptimizer: optimizes with
    SpatialQueryEngine --> DeliveryScheduler: locates vehicles
    
    %% Data processing
    DataProcessor --|> CityMapManager: used by
    DataProcessor --|> EntityManager: used by

    %% Algorithm usage
    Graph --|> CityMapManager: composed in
    QuadTree --|> SpatialQueryEngine: composed in
    DeliveryPriorityQueue --|> DeliveryScheduler: composed in
```

## Component Summary

| # | Class | Purpose |
|---|-------|---------|
| 1 | **EntityManager** | Central storage for all entities (Location, Vehicle, Customer, Delivery) |
| 2 | **Graph** | City topology and pathfinding (BFS, DFS, Dijkstra, MST, etc.) |
| 3 | **QuadTree** | Spatial indexing for efficient location queries |
| 4 | **BST** | Binary Search Tree for deadline-based sorting |
| 5 | **SegmentTree** | Range queries for traffic density analysis |
| 6 | **DeliveryPriorityQueue** | Priority queue for delivery scheduling |
| 7 | **DeliveryScheduler** | Manages delivery scheduling and vehicle assignment |
| 8 | **CityMapManager** | Manages city map, graph, and traffic updates |
| 9 | **SpatialQueryEngine** | Spatial queries (nearest vehicle, radius search) |
| 10 | **DataProcessor** | General algorithms (sort, search, closest pair) |
| 11 | **RouteOptimizer** | Route optimization using greedy algorithms |

## Data Flow Architecture

```
INPUT
  ↓
EntityManager (Database Layer)
  ↓
CityMapManager (Map & Routing Layer)
  ↓
DeliveryScheduler (Scheduling Layer)
  ↓
RouteOptimizer (Optimization Layer)
  ↓
SpatialQueryEngine (Query Layer)
  ↓
OUTPUT (Routes, Assignments, Schedules)
```

## Key Features

- **11 Main Classes** covering all system needs
- **Graph algorithms** for pathfinding (Dijkstra, BFS, DFS, MST)
- **Spatial indexing** with QuadTree for efficient searches
- **Priority-based** delivery scheduling
- **Greedy algorithms** for route optimization
- **Sorting algorithms** for data processing (MergeSort, QuickSort)
- **Range queries** for traffic analysis (SegmentTree)
