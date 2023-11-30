#include <iostream>
#include <stack>
#include <functional>

using namespace std;

/*Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
 то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

Выведите элементы в порядке in-order (слева направо).
*/

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

struct BinaryTree {
    Node* root;

    explicit BinaryTree(int rootValue) : root(new Node(rootValue)) {}

    void insert(int key, const function<bool(int, int)>& compare) const {
        Node* currentNode = root;
        Node* newNode = new Node(key);

        while (currentNode != nullptr) {
            if (compare(key, currentNode->key)) {
                if (currentNode->left == nullptr) {
                    currentNode->left = newNode;
                    return;
                }
                currentNode = currentNode->left;
            } else {
                if (currentNode->right == nullptr) {
                    currentNode->right = newNode;
                    return;
                }
                currentNode = currentNode->right;
            }
        }
    }

    void inOrderTraversal(const function<bool(int, int)>& compare, const function<void(int)>& outputFunction) const {
        stack<Node*> nodes;
        Node* currentNode = root;

        while (currentNode != nullptr || !nodes.empty()) {
            while (currentNode != nullptr) {
                nodes.push(currentNode);
                currentNode = currentNode->left;
            }

            currentNode = nodes.top();
            nodes.pop();

            outputFunction(currentNode->key);

            currentNode = currentNode->right;
        }
    }
};

int main() {
    int N;
    cin >> N;

    int rootValue;
    cin >> rootValue;

    BinaryTree tree(rootValue);

    function<bool(int, int)> compare = [](int a, int b) { return a <= b; };

    function<void(int)> outputFunction = [](int value) { cout << value << " "; };

    for (int i = 1; i < N; ++i) {
        int value;
        cin >> value;
        tree.insert(value, compare);
    }

    tree.inOrderTraversal(compare, outputFunction);

    return 0;
}