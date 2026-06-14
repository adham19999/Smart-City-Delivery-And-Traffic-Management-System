# Smart City Delivery & Traffic Management System - UML Documentation

## Overview
The system consists of 11 main classes that handle entity management, data structures, algorithms, and business logic for route optimization and delivery scheduling.

---

## 11 Main Classes

### 1. **EntityManager**
**Purpose:** Central storage and retrieval of all system entities

**Attributes:**
- `unordered_map<int, Location> locations`
- `unordered_map<int, Vehicle> vehicles`
- `unordered_map<int, Customer> customers`
- `unordered_map<int, Delivery> deliveries`

**Methods:**
```
- addLocation(location: Location) : void
- addVehicle(vehicle: Vehicle) : void
- addCustomer(customer: Customer) : void
- addDelivery(delivery: Delivery) : void
- getLocation(id: int) : Location
- getVehicle(id: int) : Vehicle
- getCustomer(id: int) : Customer
- getDelivery(id: int) : Delivery
```

---

### 2. **Graph**
**Purpose:** Core data structure for city map representation and pathfinding

**Attributes:**
- `unordered_map<int, vector<pair<int, double>>> adjList` (adjacency list with weights)

**Methods:**

#### Basic Operations
```
- addEdge(u: int, v: int, weight: double) : void
- removeEdge(u: int, v: int) : void
- updateWeight(u: int, v: int, weight: double) : void
```

#### Traversals
```
- BFS(start: int) : vector<int>
- DFS(start: int) : vector<int>
```

#### Shortest Paths
```
- Dijkstra(start: int) : vector<double>
- BellmanFord(start: int) : vector<double>
```

#### Minimum Spanning Tree
```
- PrimMST() : vector<pair<int, int>>
- KruskalMST() : vector<pair<int, int>>
```

#### DAG Operations
```
- TopologicalSort() : vector<int>
```

---

### 3. **QuadTree**
**Purpose:** Spatial indexing for efficient location queries

**Attributes:**
- `QuadTreeNode* root`

**Methods:**
```
- insert(point: Location, data: void*) : void
- nearestNeighbor(point: Location) : pair<Location, void*>
- searchRadius(center: Location, radius: double) : vector<void*>
```

**Used By:** SpatialQueryEngine

---

### 4. **BST (Binary Search Tree)**
**Purpose:** Efficient sorting and searching of deliveries by deadline

**Attributes:**
- `BSTNode* root`

**Methods:**
```
- insert(value: int) : void
- search(value: int) : BSTNode*
- remove(value: int) : void
- inorder() : vector<int>
```

**Use Case:** Sorting deliveries by deadline for scheduling

---

### 5. **SegmentTree**
**Purpose:** Range queries for traffic density analysis

**Attributes:**
- `vector<int> tree`

**Methods:**
```
- build(arr: vector<int>) : void
- query(l: int, r: int) : int
- update(index: int, value: int) : void
```

**Use Case:** Traffic density queries on road segments

---

### 6. **DeliveryPriorityQueue**
**Purpose:** Priority-based delivery processing

**Attributes:**
- `priority_queue<Delivery> heap`

**Methods:**
```
- insert(delivery: Delivery) : void
- extractMax() : Delivery
- updatePriority(deliveryId: int, priority: int) : void
```

**Used By:** DeliveryScheduler

---

### 7. **DeliveryScheduler**
**Purpose:** Schedule and assign deliveries to vehicles

**Attributes:**
- `DeliveryPriorityQueue pq`

**Methods:**
```
- scheduleDelivery(delivery: Delivery) : void
- updatePriority(deliveryId: int, priority: int) : void
- assignVehicle(delivery: Delivery) : Vehicle
```

**Dependencies:** EntityManager, DeliveryPriorityQueue, RouteOptimizer

---

### 8. **CityMapManager**
**Purpose:** Manage city map and traffic updates

**Attributes:**
- `Graph graph`

**Methods:**
```
- loadCity(filepath: string) : void
- updateTraffic(trafficEvent: TrafficEvent) : void
- findShortestPath(from: int, to: int) : vector<int>
```

**Dependencies:** Graph, DataProcessor, Road, TrafficEvent

---

### 9. **SpatialQueryEngine**
**Purpose:** Spatial queries for finding vehicles and locations

**Attributes:**
- `QuadTree quadTree`

**Methods:**
```
- findNearestVehicle(location: Location) : Vehicle
- findLocationsInRadius(center: Location, radius: double) : vector<Location>
```

**Dependencies:** QuadTree, Vehicle, Location

---

### 10. **DataProcessor**
**Purpose:** Implement sorting and searching algorithms

**Methods:**
```
- mergeSort(arr: vector<int>) : vector<int>
- quickSort(arr: vector<int>) : vector<int>
- binarySearch(arr: vector<int>, target: int) : int
- closestPair(points: vector<Location>) : pair<Location, Location>
```

**Used For:** Processing and sorting delivery data, analyzing vehicle positions

---

### 11. **RouteOptimizer**
**Purpose:** Greedy algorithms for route and vehicle optimization

**Methods:**
```
- optimizeRoute(deliveries: vector<Delivery>, vehicle: Vehicle) : vector<int>
- assignVehicles(deliveries: vector<Delivery>, vehicles: vector<Vehicle>) : map<int, vector<int>>
- selectDeliveries(deliveries: vector<Delivery>, capacity: double) : vector<int>
- fractionalKnapsack(items: vector<Item>, capacity: double) : double
```

**Algorithms Used:**
- Greedy Route Selection
- Activity Selection (non-overlapping deliveries)
- Fractional Knapsack (capacity-based selection)

---

## Class Relationships

```
                            Graph
                              ▲
                              |
                   CityMapManager

        EntityManager ----+----+----+
             |            |    |    |
             |            |    |    ▼
             |            |    | DeliveryScheduler
             |            |    |    |
             |            |    |    ▼
             |            |    DeliveryPriorityQueue
             |            |
             +----------->+-----> RouteOptimizer

     SpatialQueryEngine ---------> QuadTree

           DataProcessor

              BST (for deadline sorting)
           SegmentTree (for traffic queries)
```

---

## Detailed Relationships

### 1. **EntityManager → All Models**
- Stores and manages all Location, Vehicle, Customer, and Delivery objects
- Central point for data access

### 2. **CityMapManager → Graph**
- Builds graph from city map data
- Uses Graph for pathfinding and traffic management

### 3. **DeliveryScheduler → DeliveryPriorityQueue**
- Manages priority of deliveries
- Extracts highest priority deliveries for assignment

### 4. **DeliveryScheduler → RouteOptimizer**
- Sends deliveries for route optimization
- Receives optimized vehicle assignments

### 5. **SpatialQueryEngine → QuadTree**
- Maintains spatial index of vehicles and locations
- Performs efficient proximity searches

### 6. **DataProcessor → Sorting/Searching**
- Implements all sorting algorithms (MergeSort, QuickSort)
- Implements searching algorithms (BinarySearch, ClosestPair)
- Used by other managers for data organization

### 7. **RouteOptimizer → EntityManager**
- Gets vehicle and delivery information
- Calculates optimal routes and assignments

---

## Data Flow

```
User Input
    ↓
EntityManager (stores entities)
    ↓
CityMapManager (builds graph, finds paths)
    ↓
DeliveryScheduler (prioritizes deliveries)
    ↓
RouteOptimizer (optimizes routes)
    ↓
SpatialQueryEngine (finds nearest vehicles)
    ↓
Output (routes, assignments, schedules)
```

---

## Component Responsibilities

| Component | Responsibility |
|-----------|-----------------|
| **EntityManager** | Entity storage and retrieval |
| **Graph** | City topology and pathfinding |
| **QuadTree** | Spatial indexing |
| **BST** | Deadline-based sorting |
| **SegmentTree** | Traffic density queries |
| **DeliveryPriorityQueue** | Priority management |
| **DeliveryScheduler** | Delivery scheduling |
| **CityMapManager** | Map management and traffic updates |
| **SpatialQueryEngine** | Location and vehicle proximity queries |
| **DataProcessor** | General algorithms (sort, search) |
| **RouteOptimizer** | Route and vehicle optimization |

---

## Key Design Patterns

1. **Separation of Concerns:** Each class has a specific responsibility
2. **Data Structures:** Specialized structures for specific problems (Graph, QuadTree, BST, SegmentTree)
3. **Manager Pattern:** EntityManager, CityMapManager, DeliveryScheduler centralize operations
4. **Algorithm Encapsulation:** DataProcessor and RouteOptimizer contain algorithm implementations
5. **Composition:** Managers compose data structures (Graph in CityMapManager, QuadTree in SpatialQueryEngine)

---
