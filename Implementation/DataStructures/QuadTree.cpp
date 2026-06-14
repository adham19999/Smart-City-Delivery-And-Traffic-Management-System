#include "../../Headers/DataStructures/QuadTree.h"
#include <algorithm>
#include <limits>

// ========== QUADTREENODE IMPLEMENTATION ==========

QuadTreeNode::QuadTreeNode(double x, double y, double w, double h, int cap)
    : x(x), y(y), width(w), height(h), capacity(cap), NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}

QuadTreeNode::~QuadTreeNode()
{
    delete NW;
    delete NE;
    delete SW;
    delete SE;
}

// ========== QUADTREE IMPLEMENTATION ==========

QuadTree::QuadTree(double x, double y, double width, double height, int capacity)
{
    root = new QuadTreeNode(x, y, width, height, capacity);
    cout << "QuadTree initialized with bounds: (" << x << ", " << y << "), Size: " << width * 2 << "x" << height * 2 << "\n";
}

QuadTree::~QuadTree()
{
    delete root;
}

// ========== CORE OPERATIONS ==========

void QuadTree::insert(const Location& location)
{
    insertHelper(root, location);
    cout << "Location " << location.id << " (" << location.x << ", " << location.y << ") inserted into QuadTree.\n";
}

void QuadTree::insertHelper(QuadTreeNode* node, const Location& loc)
{
    if (!isInBounds(loc, node))
        return;

    // If node has children (already subdivided), route to correct quadrant only
    if (node->NW != nullptr)
    {
        if (isInBounds(loc, node->NW))
            insertHelper(node->NW, loc);
        else if (isInBounds(loc, node->NE))
            insertHelper(node->NE, loc);
        else if (isInBounds(loc, node->SW))
            insertHelper(node->SW, loc);
        else
            insertHelper(node->SE, loc);
        return;
    }

    // Leaf node: add location
    node->locations.push_back(loc);

    // Subdivide if capacity exceeded
    if ((int)node->locations.size() > node->capacity)
        subdivideHelper(node);
}

void QuadTree::subdivideHelper(QuadTreeNode* node)
{
    double x = node->x;
    double y = node->y;
    double w = node->width / 2.0;
    double h = node->height / 2.0;
    
    // Create four quadrants
    node->NW = new QuadTreeNode(x - w, y + h, w, h, node->capacity);  // Top-left
    node->NE = new QuadTreeNode(x + w, y + h, w, h, node->capacity);  // Top-right
    node->SW = new QuadTreeNode(x - w, y - h, w, h, node->capacity);  // Bottom-left
    node->SE = new QuadTreeNode(x + w, y - h, w, h, node->capacity);  // Bottom-right
    
    // Redistribute existing locations
    vector<Location> tempLocations = node->locations;
    node->locations.clear();
    
    for (const auto& loc : tempLocations)
    {
        if (isInBounds(loc, node->NW))
            node->NW->locations.push_back(loc);
        else if (isInBounds(loc, node->NE))
            node->NE->locations.push_back(loc);
        else if (isInBounds(loc, node->SW))
            node->SW->locations.push_back(loc);
        else if (isInBounds(loc, node->SE))
            node->SE->locations.push_back(loc);
    }
    
    cout << "Node subdivided into 4 quadrants.\n";
}

// ========== SEARCH OPERATIONS ==========

vector<Location> QuadTree::searchRadius(const Location& center, double radius) const
{
    vector<Location> result;
    searchRadiusHelper(root, center, radius, result);
    
    cout << "Found " << result.size() << " locations within radius " << radius 
         << " from (" << center.x << ", " << center.y << ")\n";
    
    return result;
}

void QuadTree::searchRadiusHelper(QuadTreeNode* node, const Location& center, double radius, vector<Location>& result) const
{
    if (node == nullptr)
        return;
    
    // Check if this node's bounding box intersects with search circle
    double circleDistX = abs(center.x - node->x);
    double circleDistY = abs(center.y - node->y);
    
    if (circleDistX > (node->width + radius) || circleDistY > (node->height + radius))
        return; // No intersection
    
    // If node has children, search them
    if (node->NW != nullptr)
    {
        searchRadiusHelper(node->NW, center, radius, result);
        searchRadiusHelper(node->NE, center, radius, result);
        searchRadiusHelper(node->SW, center, radius, result);
        searchRadiusHelper(node->SE, center, radius, result);
    }
    else
    {
        // Search points in this leaf node
        for (const auto& loc : node->locations)
        {
            double dist = center.distanceTo(loc);
            if (dist <= radius)
                result.push_back(loc);
        }
    }
}

Location* QuadTree::nearestNeighbor(const Location& point) const
{
    Location* nearest = nullptr;
    double minDist = numeric_limits<double>::max();
    
    nearestNeighborHelper(root, point, nearest, minDist);
    
    if (nearest != nullptr)
    {
        cout << "Nearest location to (" << point.x << ", " << point.y << ") is Location " 
             << nearest->id << " at distance " << minDist << "\n";
    }
    else
    {
        cout << "No locations found in QuadTree!\n";
    }
    
    return nearest;
}

Location* QuadTree::nearestNeighborHelper(QuadTreeNode* node, const Location& point, Location*& nearest, double& minDist) const
{
    if (node == nullptr)
        return nearest;
    
    // If node has children, search them
    if (node->NW != nullptr)
    {
        // Sort quadrants by distance to search nearest first (optimization)
        nearestNeighborHelper(node->NW, point, nearest, minDist);
        nearestNeighborHelper(node->NE, point, nearest, minDist);
        nearestNeighborHelper(node->SW, point, nearest, minDist);
        nearestNeighborHelper(node->SE, point, nearest, minDist);
    }
    else
    {
        // Search points in this leaf node
        for (auto& loc : node->locations)
        {
            double dist = point.distanceTo(loc);
            if (dist < minDist)
            {
                minDist = dist;
                nearest = &loc;
            }
        }
    }
    
    return nearest;
}

// ========== UTILITY OPERATIONS ==========

bool QuadTree::isInBounds(const Location& loc, QuadTreeNode* node) const
{
    return loc.x >= node->x - node->width &&
           loc.x <= node->x + node->width &&
           loc.y >= node->y - node->height &&
           loc.y <= node->y + node->height;
}

void QuadTree::display() const
{
    if (root == nullptr)
    {
        cout << "\n=== QuadTree (Empty) ===\n";
        return;
    }
    
    cout << "\n=== QuadTree Structure ===\n";
    cout << "Root Bounds: Center(" << root->x << ", " << root->y << "), Size(" 
         << root->width * 2 << "x" << root->height * 2 << ")\n";
    cout << "Capacity: " << root->capacity << "\n\n";
    
    displayHelper(root, 0);
}

void QuadTree::displayHelper(QuadTreeNode* node, int level) const
{
    if (node == nullptr)
        return;
    
    string indent(level * 4, ' ');
    
    cout << indent << "Node [(" << node->x << ", " << node->y << ") Size: " 
         << node->width * 2 << "x" << node->height * 2 << "]\n";
    
    // Display locations in this node
    if (!node->locations.empty())
    {
        cout << indent << "  Locations: ";
        for (const auto& loc : node->locations)
        {
            cout << "L" << loc.id << "(" << loc.x << "," << loc.y << ") ";
        }
        cout << "\n";
    }
    
    // Recursively display children
    if (node->NW != nullptr)
    {
        cout << indent << "  NW:\n";
        displayHelper(node->NW, level + 2);
    }
    if (node->NE != nullptr)
    {
        cout << indent << "  NE:\n";
        displayHelper(node->NE, level + 2);
    }
    if (node->SW != nullptr)
    {
        cout << indent << "  SW:\n";
        displayHelper(node->SW, level + 2);
    }
    if (node->SE != nullptr)
    {
        cout << indent << "  SE:\n";
        displayHelper(node->SE, level + 2);
    }
}

void QuadTree::clear()
{
    delete root;
    root = nullptr;
    cout << "QuadTree cleared.\n";
}

int QuadTree::countPoints() const
{
    return countPointsHelper(root);
}

int QuadTree::countPointsHelper(QuadTreeNode* node) const
{
    if (node == nullptr)
        return 0;
    
    int count = node->locations.size();
    
    if (node->NW != nullptr)
    {
        count += countPointsHelper(node->NW);
        count += countPointsHelper(node->NE);
        count += countPointsHelper(node->SW);
        count += countPointsHelper(node->SE);
    }
    
    return count;
}
