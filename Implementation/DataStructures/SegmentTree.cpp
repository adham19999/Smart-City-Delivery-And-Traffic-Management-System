#include "../../Headers/DataStructures/SegmentTree.h"
#include <algorithm>
#include <limits>

SegmentTree::SegmentTree() : n(0) {}

// ========== CORE OPERATIONS ==========

void SegmentTree::build(const vector<double>& data)
{
    arr = data;
    n = data.size();
    
    if (n == 0)
    {
        cout << "Error: Cannot build tree from empty array!\n";
        return;
    }
    
    // Initialize trees (4*n size for safety)
    tree.assign(4 * n, 0.0);
    maxTree.assign(4 * n, 0.0);
    
    buildHelper(1, 0, n - 1);
    
    cout << "Segment tree built with " << n << " elements.\n";
}

void SegmentTree::buildHelper(int node, int start, int end)
{
    if (start == end)
    {
        // Leaf node
        tree[node] = arr[start];
        maxTree[node] = arr[start];
    }
    else
    {
        int mid = (start + end) / 2;
        int leftChild = 2 * node;
        int rightChild = 2 * node + 1;
        
        // Build left and right subtrees
        buildHelper(leftChild, start, mid);
        buildHelper(rightChild, mid + 1, end);
        
        // Combine: sum and max
        tree[node] = tree[leftChild] + tree[rightChild];
        maxTree[node] = max(maxTree[leftChild], maxTree[rightChild]);
    }
}

void SegmentTree::update(int index, double value)
{
    if (index < 0 || index >= n)
    {
        cout << "Error: Index out of bounds!\n";
        return;
    }
    
    updateHelper(1, 0, n - 1, index, value);
    arr[index] = value;
    
    cout << "Updated index " << index << " to " << value << "\n";
}

void SegmentTree::updateHelper(int node, int start, int end, int idx, double value)
{
    if (start == end)
    {
        // Leaf node
        tree[node] = value;
        maxTree[node] = value;
    }
    else
    {
        int mid = (start + end) / 2;
        int leftChild = 2 * node;
        int rightChild = 2 * node + 1;
        
        if (idx <= mid)
        {
            updateHelper(leftChild, start, mid, idx, value);
        }
        else
        {
            updateHelper(rightChild, mid + 1, end, idx, value);
        }
        
        // Combine results from children
        tree[node] = tree[leftChild] + tree[rightChild];
        maxTree[node] = max(maxTree[leftChild], maxTree[rightChild]);
    }
}

// ========== QUERY OPERATIONS ==========

double SegmentTree::rangeSum(int left, int right)
{
    if (n == 0 || left < 0 || right >= n || left > right)
    {
        cout << "Error: Invalid range [" << left << ", " << right << "]\n";
        return 0.0;
    }
    
    double result = querySumHelper(1, 0, n - 1, left, right);
    cout << "Range sum [" << left << ", " << right << "] = " << result << "\n";
    return result;
}

double SegmentTree::querySumHelper(int node, int start, int end, int l, int r)
{
    if (r < start || end < l)
    {
        // No overlap
        return 0.0;
    }
    
    if (l <= start && end <= r)
    {
        // Complete overlap
        return tree[node];
    }
    
    // Partial overlap
    int mid = (start + end) / 2;
    double leftSum = querySumHelper(2 * node, start, mid, l, r);
    double rightSum = querySumHelper(2 * node + 1, mid + 1, end, l, r);
    
    return leftSum + rightSum;
}

double SegmentTree::rangeMax(int left, int right)
{
    if (n == 0 || left < 0 || right >= n || left > right)
    {
        cout << "Error: Invalid range [" << left << ", " << right << "]\n";
        return -numeric_limits<double>::max();
    }
    
    double result = queryMaxHelper(1, 0, n - 1, left, right);
    cout << "Range max [" << left << ", " << right << "] = " << result << "\n";
    return result;
}

double SegmentTree::queryMaxHelper(int node, int start, int end, int l, int r)
{
    if (r < start || end < l)
    {
        // No overlap
        return -numeric_limits<double>::max();
    }
    
    if (l <= start && end <= r)
    {
        // Complete overlap
        return maxTree[node];
    }
    
    // Partial overlap
    int mid = (start + end) / 2;
    double leftMax = queryMaxHelper(2 * node, start, mid, l, r);
    double rightMax = queryMaxHelper(2 * node + 1, mid + 1, end, l, r);
    
    return max(leftMax, rightMax);
}

double SegmentTree::rangeMin(int left, int right)
{
    if (n == 0 || left < 0 || right >= n || left > right)
    {
        cout << "Error: Invalid range [" << left << ", " << right << "]\n";
        return numeric_limits<double>::max();
    }
    
    // Linear scan for min (alternative: maintain separate min tree)
    double minVal = numeric_limits<double>::max();
    for (int i = left; i <= right; i++)
    {
        minVal = min(minVal, arr[i]);
    }
    
    cout << "Range min [" << left << ", " << right << "] = " << minVal << "\n";
    return minVal;
}

// ========== UTILITY OPERATIONS ==========

void SegmentTree::displayArray() const
{
    if (isEmpty())
    {
        cout << "\n=== Original Array (Empty) ===\n";
        return;
    }
    
    cout << "\n=== Original Array ===\n";
    cout << "Index | Value\n";
    cout << "------|-------\n";
    
    for (int i = 0; i < n; i++)
    {
        cout << i << "     | " << arr[i] << "\n";
    }
}

void SegmentTree::displayTrees() const
{
    if (isEmpty())
    {
        cout << "\n=== Segment Trees (Empty) ===\n";
        return;
    }
    
    cout << "\n=== Sum Tree (Indices) ===\n";
    cout << "Node | Value\n";
    cout << "-----|-------\n";
    
    for (int i = 1; i < tree.size() && tree[i] != 0; i++)
    {
        cout << i << "    | " << tree[i] << "\n";
    }
    
    cout << "\n=== Max Tree (Indices) ===\n";
    cout << "Node | Value\n";
    cout << "-----|-------\n";
    
    for (int i = 1; i < maxTree.size() && maxTree[i] != 0; i++)
    {
        cout << i << "    | " << maxTree[i] << "\n";
    }
}

void SegmentTree::display() const
{
    if (isEmpty())
    {
        cout << "\n=== Segment Tree (Empty) ===\n";
        return;
    }
    
    cout << "\n=== Segment Tree Information ===\n";
    cout << "Array Size: " << n << "\n";
    cout << "Tree Size: " << tree.size() << "\n";
    
    displayArray();
    displayTrees();
}

int SegmentTree::size() const
{
    return n;
}

bool SegmentTree::isEmpty() const
{
    return n == 0;
}

void SegmentTree::clear()
{
    arr.clear();
    tree.clear();
    maxTree.clear();
    n = 0;
    
    cout << "Segment tree cleared.\n";
}
