# Headers Folder Structure

This folder contains all `.h` header files organized by module type, providing clean API definitions for the Smart City Delivery And Traffic Management System.

## Structure

```
Headers/
├── Models/
│   ├── Location.h         # Geographic point representation
│   ├── Vehicle.h          # Delivery vehicle entity
│   ├── Customer.h         # Customer entity
│   ├── Delivery.h         # Delivery order entity
│   ├── Road.h             # Road/edge entity
│   └── TrafficEvent.h     # Real-time traffic event
│
├── DataStructures/
│   ├── Graph.h            # Graph algorithms (complete)
│   ├── BST.h              # Binary Search Tree
│   ├── PriorityQueue.h    # Priority Queue for deliveries
│   ├── SegmentTree.h      # Segment Tree for range queries
│   └── QuadTree.h         # QuadTree for spatial indexing
│
├── Algorithms/
│   ├── BinarySearch.h     # Binary search algorithm
│   ├── BFS.h              # Breadth-First Search
│   └── ClosestPair.h      # Closest pair algorithm
│
└── Managers/
    ├── EntityManager.h    # Manages entities (vehicles, customers, deliveries)
    ├── CityMapManager.h   # Manages city graph and road network
    ├── DeliveryScheduler.h # Schedules and assigns deliveries
    ├── DataProcessor.h    # Processes and sorts data
    └── SpatialQueryEngine.h # Handles spatial queries
```

## Class Definitions

### Models/ - Core Entities

**Location.h**
- Geographic point with coordinates (x, y)
- Methods: `distanceTo(Location)` for Euclidean distance
- Used by: Graph nodes, Vehicle positions

**Vehicle.h**
- Delivery vehicle with capacity, speed, availability
- Methods: `canCarry(weight)` for capacity check
- Fields: id, capacity, speed, currentLocation, available

**Customer.h**
- Delivery recipient information
- Fields: id, name, address, phone
- Methods: `display()`

**Delivery.h**
- Delivery order with priority and deadline
- Methods: `isOverdue(currentTime)` for deadline check
- Fields: id, customerId, pickupLocation, dropoffLocation, priority, deadline, weight, status, assignedVehicle

**Road.h**
- Edge in city graph
- Fields: from, to, weight
- Represents road connections with distance/time

**TrafficEvent.h**
- Real-time traffic condition
- Methods: `isHighSeverity()` checks if severity >= 7
- Fields: id, roadId, severity, density, timestamp

### DataStructures/ - Algorithms & Data Structures

**Graph.h** ✅ Complete Implementation
- Adjacency list representation
- All major algorithms implemented
- See Implementation/DataStructures/Graph.cpp for full implementation

**BST.h** - Binary Search Tree (pending implementation)
- For deadline sorting of deliveries

**PriorityQueue.h** - Priority Queue (pending implementation)
- For delivery priority management
- Custom comparator for Delivery objects

**SegmentTree.h** - Range Query Structure (pending implementation)
- For traffic density range queries
- Efficient O(log n) query and update

**QuadTree.h** - Spatial Index (pending implementation)
- For spatial partitioning
- Methods: insert, nearestNeighbor, searchRadius

### Algorithms/ - Utility Algorithms

**BinarySearch.h** - Searching algorithm (pending implementation)

**BFS.h** - Breadth-First Search (pending implementation)

**ClosestPair.h** - Closest pair algorithm (pending implementation)

### Managers/ - Orchestration Layer

**EntityManager.h** - Manages all entities (pending implementation)
- Stores and retrieves vehicles, customers, deliveries

**CityMapManager.h** - Manages city graph (pending implementation)
- Maintains road network
- Updates traffic conditions
- Builds graph from road data

**DeliveryScheduler.h** - Scheduling logic (pending implementation)
- Assigns deliveries to vehicles
- Respects capacity and deadline constraints

**DataProcessor.h** - Data processing (pending implementation)
- Sorting algorithms (MergeSort, QuickSort)
- Data aggregation and analysis

**SpatialQueryEngine.h** - Spatial queries (pending implementation)
- Finds nearby locations
- Proximity searches

## Include Paths

Files in the project should include headers as follows:

**From Implementation/Models/*.cpp:**
```cpp
#include "../../Headers/Models/Location.h"
```

**From Implementation/DataStructures/*.cpp:**
```cpp
#include "../../Headers/DataStructures/Graph.h"
```

**From Implementation/Algorithms/*.cpp:**
```cpp
#include "../../Headers/Algorithms/BinarySearch.h"
```

**From Implementation/Managers/*.cpp:**
```cpp
#include "../../Headers/Managers/EntityManager.h"
```

## Compilation Command

```bash
g++ -std=c++17 -I. Implementation/Models/*.cpp \
                   Implementation/DataStructures/Graph.cpp \
                   -o smart_city_app
```


