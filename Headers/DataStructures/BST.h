#ifndef BST_H
#define BST_H

#include "../Models/Delivery.h"
#include <vector>
#include <iostream>

using namespace std;

struct BSTNode
{
    Delivery delivery;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(const Delivery& d) : delivery(d), left(nullptr), right(nullptr) {}
};

class DeliveryBST
{
private:
    BSTNode* root;
    
    // Helper functions (recursive)
    BSTNode* insertHelper(BSTNode* node, const Delivery& delivery);
    BSTNode* removeHelper(BSTNode* node, int deliveryId);
    BSTNode* searchHelper(BSTNode* node, int deliveryId) const;
    BSTNode* findMinNode(BSTNode* node) const;
    BSTNode* findMaxNode(BSTNode* node) const;
    int heightHelper(BSTNode* node) const;
    void inorderHelper(BSTNode* node, vector<Delivery>& result) const;
    void preorderHelper(BSTNode* node, vector<Delivery>& result) const;
    void postorderHelper(BSTNode* node, vector<Delivery>& result) const;
    void clearHelper(BSTNode* node);
    void displayHelper(BSTNode* node, int level) const;
    
public:
    DeliveryBST();
    ~DeliveryBST();
    
    // Core operations
    void insert(const Delivery& delivery);
    void remove(int deliveryId);
    Delivery* search(int deliveryId);
    
    // Boundary operations
    Delivery findMin() const;
    Delivery findMax() const;
    
    // Traversals
    vector<Delivery> inorderTraversal() const;
    vector<Delivery> preorderTraversal() const;
    vector<Delivery> postorderTraversal() const;
    
    // Utility operations
    int height() const;
    bool isEmpty() const;
    void display() const;
    void clear();
    int countNodes() const;
};

#endif // BST_H
