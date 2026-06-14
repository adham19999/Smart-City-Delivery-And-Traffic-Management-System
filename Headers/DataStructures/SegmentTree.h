#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

#include <vector>
#include <iostream>

using namespace std;

class SegmentTree
{
private:
    vector<double> tree;      // Sum tree
    vector<double> maxTree;   // Max tree
    vector<double> arr;       // Original array
    int n;
    
    // Helper functions
    void buildHelper(int node, int start, int end);
    void updateHelper(int node, int start, int end, int idx, double value);
    double querySumHelper(int node, int start, int end, int l, int r);
    double queryMaxHelper(int node, int start, int end, int l, int r);
    
public:
    SegmentTree();
    ~SegmentTree() = default;
    
    // Core operations
    void build(const vector<double>& data);
    void update(int index, double value);
    
    // Query operations
    double rangeSum(int left, int right);
    double rangeMax(int left, int right);
    double rangeMin(int left, int right);
    
    // Utility operations
    void display() const;
    int size() const;
    bool isEmpty() const;
    void clear();
    void displayArray() const;
    void displayTrees() const;
};

#endif // SEGMENTTREE_H
