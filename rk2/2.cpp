#include <iostream>
#include <queue>

using namespace std;

/*
Напишите функцию, вычисляющую кратчайшее расстояние от корня дерева до листа.
Значения - int.
*/

// Структура для представления узла бинарного дерева
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Структура для представления бинарного дерева
struct BinTree {
    TreeNode* root;

    BinTree() : root(nullptr) {}

    ~BinTree() {
        clearTree(root);
    }

    // Рекурсивный метод для очистки памяти дерева
    void clearTree(TreeNode* current) {
        if (current != nullptr) {
            clearTree(current->left);
            clearTree(current->right);
            delete current;
        }
    }

    // Метод для вставки нового узла в бинарное дерево
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Рекурсивный метод для вставки нового узла в бинарное дерево
    TreeNode* insertRecursive(TreeNode* current, int value) {
        if (current == nullptr) {
            return new TreeNode(value);
        }

        if (value < current->data) {
            current->left = insertRecursive(current->left, value);
        } else {
            current->right = insertRecursive(current->right, value);
        }

        return current;
    }

    // Метод для вычисления кратчайшего расстояния от корня до листа
    int shortestPath() {
        if (root == nullptr) {
            return 0;
        }

        queue<pair<TreeNode*, int>> q;
        q.emplace(root, 1);

        while (!q.empty()) {
            TreeNode* current = q.front().first;
            int level = q.front().second;
            q.pop();

            // Если узел является листом, возвращаем текущий уровень
            if (current->left == nullptr && current->right == nullptr) {
                return level;
            }

            // Добавляем дочерние узлы в очередь с увеличением уровня
            if (current->left != nullptr) {
                q.emplace(current->left, level + 1);
            }
            if (current->right != nullptr) {
                q.emplace(current->right, level + 1);
            }
        }

        return 0;
    }
};

int main() {
    BinTree tree;

    int value;
    while (cin >> value) {
        tree.insert(value);
    }

    cout << tree.shortestPath() << endl;

    return 0;
}
