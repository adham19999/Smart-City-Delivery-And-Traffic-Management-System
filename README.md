# Smart City Delivery & Traffic Management System

A comprehensive C++ system for managing city deliveries and traffic optimization using advanced data structures and algorithms.

## System Overview

![System Architecture](delivery_system.svg)

## Project Structure

```
SmartCityProject
│
├── main.cpp
│
├── Models
│     ├── Location.h
│     ├── Vehicle.h
│     ├── Customer.h
│     ├── Delivery.h
│     ├── Road.h
│     └── TrafficEvent.h
│
├── DataStructures
│     ├── Graph.h
│     ├── BST.h
│     ├── SegmentTree.h
│     ├── QuadTree.h
│     └── PriorityQueue.h
│
├── Algorithms
│     ├── MergeSort.h
│     ├── QuickSort.h
│     ├── BinarySearch.h
│     ├── ClosestPair.h
│     ├── RouteOptimizer.h
│     └── ZonePartition.h
│
├── Managers
│     ├── EntityManager.h
│     ├── CityMapManager.h
│     ├── SpatialQueryEngine.h
│     ├── DeliveryScheduler.h
│     └── DataProcessor.h
│
├── Data
│     ├── city_map.txt
│     ├── vehicles.txt
│     ├── deliveries.txt
│     └── locations.txt
│
└── UML
      ├── ClassDiagram.puml
      ├── UML_Documentation.md
      ├── Mermaid_Diagram.md
      └── ASCII_Diagram.txt
```

## 11 Core Classes

| Class | Purpose |
|-------|---------|
| **EntityManager** | Central storage and retrieval of all entities (Location, Vehicle, Customer, Delivery) |
| **Graph** | City topology and pathfinding (BFS, DFS, Dijkstra, MST, Topological Sort) |
| **QuadTree** | Spatial indexing for efficient location and vehicle queries |
| **BST** | Binary Search Tree for deadline-based delivery sorting |
| **SegmentTree** | Range queries for traffic density analysis |
| **DeliveryPriorityQueue** | Priority queue for delivery management |
| **DeliveryScheduler** | Coordinates delivery scheduling and vehicle assignment |
| **CityMapManager** | Manages city map, graph, and traffic updates |
| **SpatialQueryEngine** | Performs spatial queries (nearest vehicle, radius search) |
| **DataProcessor** | Implements sorting and searching algorithms |
| **RouteOptimizer** | Greedy algorithms for route and vehicle optimization |

## Key Features

- **Graph Algorithms**: Dijkstra, BellmanFord, Prim MST, Kruskal MST, BFS, DFS, Topological Sort
- **Spatial Indexing**: QuadTree for efficient proximity searches
- **Data Structures**: BST for sorting, SegmentTree for range queries, Priority Queue
- **Sorting Algorithms**: MergeSort, QuickSort
- **Search Algorithms**: BinarySearch, ClosestPair
- **Optimization**: Greedy route optimization, activity selection, fractional knapsack

## Data Models

### Location
```cpp
- id: int
- name: string
- x, y: coordinates
- type: string
```

### Vehicle
```cpp
- id: int
- capacity: double
- speed: double
- currentLocation: int
- available: bool
```

### Delivery
```cpp
- id: int
- customerId: int
- pickupLocation, dropoffLocation: int
- deadline: datetime
- priority: int
- status: string
```

### Customer
```cpp
- id: int
- name: string
- address: string
- phone: string
```

## System Workflow

```
User Input
    ↓
EntityManager (Store entities)
    ↓
CityMapManager (Build graph, find paths)
    ↓
DeliveryScheduler (Prioritize deliveries)
    ↓
RouteOptimizer (Optimize routes)
    ↓
SpatialQueryEngine (Find nearest vehicles)
    ↓
Output (Routes, Assignments, Schedules)
```

## Building & Compilation

```bash
g++ -std=c++17 -o smart_city main.cpp
```

## Usage

The system processes deliveries through multiple stages:

1. **Entity Management**: Register locations, vehicles, customers, and deliveries
2. **Map Processing**: Load city map and establish connections
3. **Scheduling**: Prioritize deliveries based on deadline and importance
4. **Optimization**: Calculate optimal routes and vehicle assignments
5. **Queries**: Find nearest vehicles and locations within radius

## Files

- `/Models` - Core entity definitions
- `/DataStructures` - Graph, BST, SegmentTree, QuadTree, PriorityQueue
- `/Algorithms` - Sorting, searching, and optimization algorithms
- `/Managers` - Business logic and orchestration
- `/Data` - Configuration and data files
- `/UML` - Complete UML documentation and diagrams

## Documentation

- [UML Documentation](UML/UML_Documentation.md) - Detailed class specifications
- [Mermaid Diagram](UML/Mermaid_Diagram.md) - Interactive diagram
- [ASCII Diagram](UML/ASCII_Diagram.txt) - Text-based architecture

## License

This project is part of the Smart City course at Edges Software.

---

**Last Updated**: June 2026
