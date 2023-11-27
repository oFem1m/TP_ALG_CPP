#include <iostream>
#include <algorithm>

using namespace std;

/*
Реализуйте AVL-дерево. Решения с использованием других структур засчитываться не будут.

Входной файл содержит описание операций с деревом. Операций не больше 10^5.

Формат ввода
В каждой строке находится одна из следующих операций:

insert x — добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать не надо.
delete x — удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо.
exists x — если ключ x есть в дереве, вывести «true», иначе «false»
next x — минимальный элемент в дереве, больший x, или «none», если такого нет.
prev x — максимальный элемент в дереве, меньший x, или «none», если такого нет.
Все числа во входном файле целые и по модулю не превышают 10^9.

Формат вывода
Выведите последовательно результат выполнения всех операций exists, next, prev.
Следуйте формату выходного файла из примера.
*/

class AVLTree {
private:
    struct Node {
        int key, height;
        Node *left, *right;

        Node(int value) : key(value), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        if (node != nullptr)
            node->height = max(height(node->left), height(node->right)) + 1;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);

        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr)
            return new Node(key);

        if (key < root->key)
            root->left = insert(root->left, key);
        else if (key > root->key)
            root->right = insert(root->right, key);
        else
            return root;

        return balance(root);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        return balance(root);
    }

    bool search(Node* root, int key) {
        if (root == nullptr)
            return false;

        if (key < root->key)
            return search(root->left, key);
        else if (key > root->key)
            return search(root->right, key);
        else
            return true;
    }

    int findNext(Node* root, int key) {
        int next = -1;
        while (root != nullptr) {
            if (root->key > key) {
                next = root->key;
                root = root->left;
            } else
                root = root->right;
        }
        return next;
    }

    int findPrev(Node* root, int key) {
        int prev = -1;
        while (root != nullptr) {
            if (root->key < key) {
                prev = root->key;
                root = root->right;
            } else
                root = root->left;
        }
        return prev;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    bool exists(int key) {
        return search(root, key);
    }

    int next(int key) {
        return findNext(root, key);
    }

    int prev(int key) {
        return findPrev(root, key);
    }

    void inorderTraversal(Node* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);
            cout << root->key << endl;
            inorderTraversal(root->right);
        }
    }
};

int main() {
    AVLTree avlTree;

    string operation;
    int key;

    while (cin >> operation) {
        if (operation == "insert") {
            cin >> key;
            avlTree.insert(key);
        } else if (operation == "delete") {
            cin >> key;
            avlTree.remove(key);
        } else if (operation == "exists") {
            cin >> key;
            cout << (avlTree.exists(key) ? "true" : "false") << endl;
        } else if (operation == "next") {
            cin >> key;
            int next = avlTree.next(key);
            cout << (next == -1 ? "none" : to_string(next)) << endl;
        } else if (operation == "prev") {
            cin >> key;
            int prev = avlTree.prev(key);
            cout << (prev == -1 ? "none" : to_string(prev)) << endl;
        }
    }

    return 0;
}
