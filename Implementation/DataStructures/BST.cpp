#include "../../Headers/DataStructures/BST.h"

DeliveryBST::DeliveryBST() : root(nullptr) {}

DeliveryBST::~DeliveryBST()
{
    clear();
}

// ========== CORE OPERATIONS ==========

void DeliveryBST::insert(const Delivery& delivery)
{
    root = insertHelper(root, delivery);
    cout << "Delivery " << delivery.id << " (Deadline: " << delivery.deadline << ") inserted into BST.\n";
}

BSTNode* DeliveryBST::insertHelper(BSTNode* node, const Delivery& delivery)
{
    if (node == nullptr)
    {
        return new BSTNode(delivery);
    }
    
    // Compare by deadline (primary) then by ID (secondary)
    if (delivery.deadline < node->delivery.deadline)
    {
        node->left = insertHelper(node->left, delivery);
    }
    else if (delivery.deadline > node->delivery.deadline)
    {
        node->right = insertHelper(node->right, delivery);
    }
    else
    {
        // Same deadline, use ID for secondary ordering
        if (delivery.id < node->delivery.id)
            node->left = insertHelper(node->left, delivery);
        else
            node->right = insertHelper(node->right, delivery);
    }
    
    return node;
}

void DeliveryBST::remove(int deliveryId)
{
    root = removeHelper(root, deliveryId);
    cout << "Delivery " << deliveryId << " removed from BST (if existed).\n";
}

BSTNode* DeliveryBST::removeHelper(BSTNode* node, int deliveryId)
{
    if (node == nullptr)
        return nullptr;

    if (node->delivery.id == deliveryId)
    {
        // Case 1: No children (leaf node)
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }

        // Case 2: One child
        if (node->left == nullptr)
        {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }

        if (node->right == nullptr)
        {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: Two children — replace with inorder successor
        BSTNode* minRight = findMinNode(node->right);
        node->delivery = minRight->delivery;
        node->right = removeHelper(node->right, minRight->delivery.id);
        return node;
    }

    // Tree is ordered by deadline, not ID — search both subtrees
    node->left = removeHelper(node->left, deliveryId);
    node->right = removeHelper(node->right, deliveryId);
    return node;
}

Delivery* DeliveryBST::search(int deliveryId)
{
    BSTNode* result = searchHelper(root, deliveryId);
    if (result != nullptr)
    {
        cout << "Delivery " << deliveryId << " found in BST.\n";
        return &result->delivery;
    }
    
    cout << "Delivery " << deliveryId << " not found in BST.\n";
    return nullptr;
}

BSTNode* DeliveryBST::searchHelper(BSTNode* node, int deliveryId) const
{
    if (node == nullptr)
        return nullptr;

    if (node->delivery.id == deliveryId)
        return node;

    // Tree is ordered by deadline, not ID — must scan both subtrees
    BSTNode* found = searchHelper(node->left, deliveryId);
    if (found != nullptr)
        return found;
    return searchHelper(node->right, deliveryId);
}

// ========== BOUNDARY OPERATIONS ==========

Delivery DeliveryBST::findMin() const
{
    if (root == nullptr)
    {
        cout << "Error: BST is empty!\n";
        return Delivery();
    }
    
    BSTNode* minNode = findMinNode(root);
    cout << "Minimum deadline delivery: " << minNode->delivery.id << " (Deadline: " 
         << minNode->delivery.deadline << ")\n";
    return minNode->delivery;
}

BSTNode* DeliveryBST::findMinNode(BSTNode* node) const
{
    while (node->left != nullptr)
        node = node->left;
    return node;
}

Delivery DeliveryBST::findMax() const
{
    if (root == nullptr)
    {
        cout << "Error: BST is empty!\n";
        return Delivery();
    }
    
    BSTNode* maxNode = findMaxNode(root);
    cout << "Maximum deadline delivery: " << maxNode->delivery.id << " (Deadline: " 
         << maxNode->delivery.deadline << ")\n";
    return maxNode->delivery;
}

BSTNode* DeliveryBST::findMaxNode(BSTNode* node) const
{
    while (node->right != nullptr)
        node = node->right;
    return node;
}

// ========== TRAVERSALS ==========

vector<Delivery> DeliveryBST::inorderTraversal() const
{
    vector<Delivery> result;
    inorderHelper(root, result);
    return result;
}

void DeliveryBST::inorderHelper(BSTNode* node, vector<Delivery>& result) const
{
    if (node == nullptr)
        return;
    
    inorderHelper(node->left, result);
    result.push_back(node->delivery);
    inorderHelper(node->right, result);
}

vector<Delivery> DeliveryBST::preorderTraversal() const
{
    vector<Delivery> result;
    preorderHelper(root, result);
    return result;
}

void DeliveryBST::preorderHelper(BSTNode* node, vector<Delivery>& result) const
{
    if (node == nullptr)
        return;
    
    result.push_back(node->delivery);
    preorderHelper(node->left, result);
    preorderHelper(node->right, result);
}

vector<Delivery> DeliveryBST::postorderTraversal() const
{
    vector<Delivery> result;
    postorderHelper(root, result);
    return result;
}

void DeliveryBST::postorderHelper(BSTNode* node, vector<Delivery>& result) const
{
    if (node == nullptr)
        return;
    
    postorderHelper(node->left, result);
    postorderHelper(node->right, result);
    result.push_back(node->delivery);
}

// ========== UTILITY OPERATIONS ==========

int DeliveryBST::height() const
{
    return heightHelper(root);
}

int DeliveryBST::heightHelper(BSTNode* node) const
{
    if (node == nullptr)
        return -1;
    
    int leftHeight = heightHelper(node->left);
    int rightHeight = heightHelper(node->right);
    
    return 1 + max(leftHeight, rightHeight);
}

bool DeliveryBST::isEmpty() const
{
    return root == nullptr;
}

int DeliveryBST::countNodes() const
{
    vector<Delivery> inorder = inorderTraversal();
    return inorder.size();
}

void DeliveryBST::display() const
{
    if (isEmpty())
    {
        cout << "\n=== BST (Empty) ===\n";
        return;
    }
    
    cout << "\n=== BST Structure (Sorted by Deadline) ===\n";
    displayHelper(root, 0);
    
    cout << "\n=== BST Inorder Traversal ===\n";
    vector<Delivery> inorder = inorderTraversal();
    cout << "DeliveryID | Deadline | Customer | Priority | Status\n";
    cout << "-----------|----------|----------|----------|--------\n";
    
    for (const auto& d : inorder)
    {
        cout << d.id << "         | " << d.deadline << "       | " 
             << d.customerId << "       | " << d.priority << "        | " 
             << d.status << "\n";
    }
    
    cout << "\nBST Height: " << height() << "\n";
    cout << "Total Nodes: " << countNodes() << "\n";
}

void DeliveryBST::displayHelper(BSTNode* node, int level) const
{
    if (node == nullptr)
        return;
    
    displayHelper(node->right, level + 1);
    
    for (int i = 0; i < level; i++)
        cout << "    ";
    
    cout << "[D" << node->delivery.id << ":DL" << node->delivery.deadline << "]\n";
    
    displayHelper(node->left, level + 1);
}

void DeliveryBST::clear()
{
    clearHelper(root);
    root = nullptr;
    cout << "BST cleared.\n";
}

void DeliveryBST::clearHelper(BSTNode* node)
{
    if (node == nullptr)
        return;
    
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}
