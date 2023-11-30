#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне [0..2^32-1]
Требования:

B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Формат ввода
Сначала вводится минимальный порядок дерева t.
Затем вводятся элементы дерева.

Формат вывода
Программа должна вывести B-дерево по слоям.
Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.
*/

template <typename Key, typename Compare = less<Key>>
class BTree {
private:
    struct BNode {
        vector<Key> keys;
        vector<BNode*> children;

        BNode() = default;
        explicit BNode(const Key& key) : keys({key}) {}
    };

    BNode* root;
    int t;
    Compare compare;

public:
    explicit BTree(int order) : root(nullptr), t(order) {}

    // Вставка ключа в B-дерево
    void insert(const Key& key) {
        if (root == nullptr)
            root = new BNode(key);
        else {
            if (root->keys.size() == 2 * t - 1) {
                auto* newRoot = new BNode();
                newRoot->children.push_back(root);
                splitChild(newRoot, 0);
                root = newRoot;
            }
            insertNonFull(root, key);
        }
    }

    void insertNonFull(BNode* node, const Key& key) {
        int i = node->keys.size() - 1;
        if (node->children.empty()) {
            // Узел листа
            node->keys.push_back(Key());
            while (i >= 0 && compare(key, node->keys[i])) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        } else {
            // Внутренний узел
            while (i >= 0 && compare(key, node->keys[i]))
                i--;
            i++;

            if (node->children[i]->keys.size() == 2 * t - 1) {
                splitChild(node, i);
                if (compare(node->keys[i], key))
                    i++;
            }

            insertNonFull(node->children[i], key);
        }
    }

    void splitChild(BNode* parent, int index) {
        BNode* child = parent->children[index];
        auto* newChild = new BNode();
        parent->keys.insert(parent->keys.begin() + index, child->keys[t - 1]);
        parent->children.insert(parent->children.begin() + index + 1, newChild);

        // Перемещение второй половины ключей и детей в нового ребенка
        newChild->keys.insert(newChild->keys.begin(), child->keys.begin() + t, child->keys.end());
        child->keys.erase(child->keys.begin() + t - 1, child->keys.end());

        if (!child->children.empty()) {
            newChild->children.insert(newChild->children.begin(), child->children.begin() + t, child->children.end());
            child->children.erase(child->children.begin() + t, child->children.end());
        }
    }

    // возвращение B-дерева по слоям
    vector<vector<Key>> returnBTree() {
        vector<vector<Key>> result;
        if (root == nullptr) {
            return result;
        }

        queue<BNode*> nodeQueue;
        nodeQueue.push(root);
        int i = 0;

        while (!nodeQueue.empty()) {
            vector<Key> slice;
            int nodesInCurrentLevel = nodeQueue.size();

            while (nodesInCurrentLevel > 0) {
                BNode* currentNode = nodeQueue.front();
                nodeQueue.pop();

                for (const Key& key : currentNode->keys)
                    slice.push_back(key);

                for (BNode* child : currentNode->children)
                    if (child != nullptr)
                        nodeQueue.push(child);

                nodesInCurrentLevel--;
            }

            result.push_back(slice);
        }
        return result;
    }
};

int main() {
    int t;
    cin >> t;

    BTree<int> bTree(t);

    int key;
    while (cin >> key) {
        if (key == -1)
            break;
        bTree.insert(key);
    }
    vector<vector<int>> result;

    result = bTree.returnBTree();

    for (const auto& i: result){
        for (auto j: i)
            cout << j << " ";
        cout << endl;
    }

    return 0;
}
