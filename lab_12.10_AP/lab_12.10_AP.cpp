#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

void insert(Node*& root, int data, int level = 0) {
    if (!root) {
        root = new Node(data);
        return;
    }
    if (data < root->data)
        insert(root->left, data, level + 1);
    else
        insert(root->right, data, level + 1);
}

void printTree(Node* root, int space = 0, int height = 3) {
    if (!root) return;
    space += height;
    printTree(root->right, space);
    std::cout << std::endl;
    for (int i = height; i < space; i++)
        std::cout << " ";
    std::cout << root->data << "\n";
    printTree(root->left, space);
}

int findLevel(Node* root, int data, int level = 0) {
    if (!root) return -1;
    if (root->data == data) return level;
    int leftLevel = findLevel(root->left, data, level + 1);
    int rightLevel = findLevel(root->right, data, level + 1);
    if (leftLevel != -1)
        return leftLevel;
    else if (rightLevel != -1)
        return rightLevel;
    else
        return -1;
}

void findMinMax(Node* root, Node*& minNode, Node*& maxNode) {
    if (!root) return;
    if (!minNode || root->data < minNode->data)
        minNode = root;
    if (!maxNode || root->data > maxNode->data)
        maxNode = root;
    findMinMax(root->left, minNode, maxNode);
    findMinMax(root->right, minNode, maxNode);
}

int main() {
    std::ifstream file("D:\\laba10.txt");
    int data;
    Node* root = nullptr;
    while (file >> data)
        insert(root, data);

    std::cout << "Original tree:" << std::endl;
    printTree(root);

    Node* minNode = nullptr;
    Node* maxNode = nullptr;
    findMinMax(root, minNode, maxNode);

    std::cout << "Min value: " << minNode->data << ", level: " << findLevel(root, minNode->data) << std::endl;
    std::cout << "Max value: " << maxNode->data << ", level: " << findLevel(root, maxNode->data) << std::endl;

    std::swap(minNode->data, maxNode->data);

    std::cout << "Modified tree:" << std::endl;
    printTree(root);

    return 0;
}
