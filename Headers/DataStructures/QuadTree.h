#ifndef QUADTREE_H
#define QUADTREE_H

#include "../Models/Location.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

struct QuadTreeNode
{
    double x;           // Center x-coordinate
    double y;           // Center y-coordinate
    double width;       // Half-width (half of total width)
    double height;      // Half-height (half of total height)
    
    vector<Location> locations;  // Points in this node
    int capacity;                 // Max points before subdivision
    
    QuadTreeNode* NW;   // Northwest quadrant
    QuadTreeNode* NE;   // Northeast quadrant
    QuadTreeNode* SW;   // Southwest quadrant
    QuadTreeNode* SE;   // Southeast quadrant
    
    QuadTreeNode(double x, double y, double w, double h, int cap = 4);
    ~QuadTreeNode();
};

class QuadTree
{
private:
    QuadTreeNode* root;
    
    // Helper functions
    bool isInBounds(const Location& loc, QuadTreeNode* node) const;
    void insertHelper(QuadTreeNode* node, const Location& loc);
    void subdivideHelper(QuadTreeNode* node);
    void searchRadiusHelper(QuadTreeNode* node, const Location& center, double radius, vector<Location>& result) const;
    Location* nearestNeighborHelper(QuadTreeNode* node, const Location& point, Location*& nearest, double& minDist) const;
    void displayHelper(QuadTreeNode* node, int level) const;
    void clearHelper(QuadTreeNode* node);
    int countPointsHelper(QuadTreeNode* node) const;
    
public:
    QuadTree(double x, double y, double width, double height, int capacity = 4);
    ~QuadTree();
    
    // Core operations
    void insert(const Location& location);
    
    // Search operations
    vector<Location> searchRadius(const Location& center, double radius) const;
    Location* nearestNeighbor(const Location& point) const;
    
    // Utility operations
    void display() const;
    void clear();
    int countPoints() const;
};

#endif // QUADTREE_H
