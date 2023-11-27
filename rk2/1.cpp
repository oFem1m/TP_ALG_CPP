#include <iostream>

using namespace std;

/*
Напишите функцию, проверяющую, что во всех узлах бинарного дерева поиска хранится одинаковое значение.
Значения - int.
*/

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node *root;

    void destroyTree(Node *node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroyTree(root);
    }

    void insert(int value) {
        root = insertRec(root, value);
    }

    Node *insertRec(Node *node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }

    void inOrderTraversal(Node *node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    bool isValuesEqual(Node *node, int value) {
        if (node == nullptr) {
            return true;
        }

        return (node->data == value) &&
               isValuesEqual(node->left, value) &&
               isValuesEqual(node->right, value);
    }

    bool areAllValuesEqual() {
        if (root == nullptr) {
            return true;
        }

        int targetValue = root->data;
        return isValuesEqual(root, targetValue);
    }
};

int main() {
    BinaryTree tree;

    int value;
    while (cin >> value) {
        tree.insert(value);
    }

    if (tree.areAllValuesEqual()) {
        cout << "1" << endl;
    } else {
        cout << "0" << endl;
    }

    return 0;
}
