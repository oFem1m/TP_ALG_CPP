#include <iostream>
#include <vector>
#include <stack>

class AVLTree {
public:
    struct CNode {
        int Key;
        int Height;
        int Number;
        CNode *Left;
        CNode *Right;

        explicit CNode(int key) : Key(key), Height(1), Left(nullptr), Right(nullptr), Number(1) {}
    };

    AVLTree() : root(nullptr) {}

    CNode *InsertAndGetPos(int key, int &pos) {
        root = InsertAndGetPos(root, key, pos);
        return root;
    }

    CNode *Remove(int position) {
        root = Remove(root, position);
        return root;
    }

private:
    CNode *root;

    int Height(CNode *node) {
        return node == nullptr ? 0 : node->Height;
    }

    int Number(CNode *node) {
        return node == nullptr ? 0 : node->Number;
    }

    int BalanceFactor(CNode *node) {
        return Height(node->Right) - Height(node->Left);
    }

    CNode *RotateRight(CNode *p) {
        CNode *pR = p->Left;
        p->Left = pR->Right;
        pR->Right = p;
        p->Height = std::max(Height(p->Left), Height(p->Right)) + 1;
        p->Number = Number(p->Left) + Number(p->Right) + 1;
        pR->Height = std::max(Height(pR->Left), Height(pR->Right)) + 1;
        pR->Number = Number(pR->Left) + Number(pR->Right) + 1;
        return pR;
    }

    CNode *RotateLeft(CNode *p) {
        CNode *pL = p->Right;
        p->Right = pL->Left;
        pL->Left = p;
        p->Height = std::max(Height(p->Left), Height(p->Right)) + 1;
        p->Number = Number(p->Left) + Number(p->Right) + 1;
        pL->Height = std::max(Height(pL->Left), Height(pL->Right)) + 1;
        pL->Number = Number(pL->Left) + Number(pL->Right) + 1;
        return pL;
    }

    CNode *Balance(CNode *p) {
        p->Height = std::max(Height(p->Left), Height(p->Right)) + 1;
        p->Number = Number(p->Left) + Number(p->Right) + 1;

        if (BalanceFactor(p) == 2) {
            if (BalanceFactor(p->Right) < 0)
                p->Right = RotateRight(p->Right);
            return RotateLeft(p);
        }
        if (BalanceFactor(p) == -2) {
            if (BalanceFactor(p->Left) > 0)
                p->Left = RotateLeft(p->Left);
            return RotateRight(p);
        }
        return p;
    }

    CNode *InsertAndGetPos(CNode *root, int key, int &pos) {
        if (root == nullptr) {
            return new CNode(key);
        }
        ++(root->Number);
        if (key < root->Key) {
            pos += Number(root->Right) + 1;
            root->Left = InsertAndGetPos(root->Left, key, pos);
        } else {
            root->Right = InsertAndGetPos(root->Right, key, pos);
        }
        return Balance(root);
    }

    CNode *FindMin(CNode *p) {
        return p->Left == nullptr ? p : FindMin(p->Left);
    }

    CNode *RemoveMin(CNode *p) {
        if (p->Left == nullptr)
            return p->Right;
        p->Left = RemoveMin(p->Left);
        --p->Number;
        return Balance(p);
    }

    CNode *Remove(CNode *p, int position) {
        if (p == nullptr)
            return nullptr;
        if (position >= p->Number)
            return p;

        int sum = 0;
        std::stack<CNode *> nodes;

        while (p != nullptr) {
            int rightNumber = Number(p->Right);

            if (position - sum > rightNumber) {
                nodes.push(p);
                p = p->Left;
                sum += rightNumber + 1;
            } else if (position - sum < rightNumber) {
                if (p->Right != nullptr) {
                    nodes.push(p);
                    p = p->Right;
                } else {
                    break;
                }
            } else {
                CNode *left = p->Left;
                CNode *right = p->Right;
                int key = p->Key;
                delete p;

                if (right == nullptr) {
                    if (left == nullptr) {
                        if (!nodes.empty()) {
                            p = nodes.top();
                            nodes.pop();
                            if (p->Key > key) {
                                p->Left = nullptr;
                            } else {
                                p->Right = nullptr;
                            }
                            --p->Number;
                        } else {
                            return nullptr;
                        }
                    } else {
                        p = left;
                    }
                } else {
                    CNode *min = FindMin(right);
                    min->Right = RemoveMin(right);
                    min->Left = left;
                    p = Balance(min);
                }
                break;
            }
        }
        CNode *p1;
        while (!nodes.empty()) {
            p1 = nodes.top();
            --p1->Number;
            if (p1->Key > p->Key) {
                p1->Left = p;
            } else {
                p1->Right = p;
            }
            p = Balance(p1);
            nodes.pop();
        }
        return p;
    }
};

int main() {
    AVLTree avlTree;
    int n;
    std::cin >> n;
    std::vector<int> result;
    int key;
    int position;
    int operation;
    for (int i = 0; i < n; ++i) {
        std::cin >> operation;
        if (operation == 1) {
            position = 0;
            std::cin >> key;
            avlTree.InsertAndGetPos(key, position);
            result.push_back(position);
        } else if (operation == 2) {
            std::cin >> key;
            avlTree.Remove(key);
        }
    }
    for (int i: result) {
        std::cout << i << std::endl;
    }

    return 0;
}
