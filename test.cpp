#include <iostream>
#include <vector>
#include <stack>
#include <functional>

using namespace std;

class AVLTree {
public:
    struct TreeNode {
        int Key;
        int Height;
        int Number;
        TreeNode *Left;
        TreeNode *Right;

        explicit TreeNode(int key) : Key(key), Height(1), Left(nullptr), Right(nullptr), Number(1) {}
    };

    using CompareFunction = std::function<bool(int, int)>;

    explicit AVLTree(CompareFunction compareFunc) : root(nullptr), compareFunction(compareFunc) {}

    TreeNode *InsertAndGetPos(int key, int &pos) {
        root = InsertAndGetPos(root, key, pos);
        return root;
    }

    TreeNode *Remove(int position) {
        root = Remove(root, position);
        return root;
    }

private:
    TreeNode *root;
    CompareFunction compareFunction;

    static int Height(TreeNode *node) {
        return node == nullptr ? 0 : node->Height;
    }

    static int Number(TreeNode *node) {
        return node == nullptr ? 0 : node->Number;
    }

    static int BalanceFactor(TreeNode *node) {
        return Height(node->Right) - Height(node->Left);
    }

    static TreeNode *RotateRight(TreeNode *p) {
        TreeNode *pR = p->Left;
        p->Left = pR->Right;
        pR->Right = p;
        p->Height = max(Height(p->Left), Height(p->Right)) + 1;
        p->Number = Number(p->Left) + Number(p->Right) + 1;
        pR->Height = max(Height(pR->Left), Height(pR->Right)) + 1;
        pR->Number = Number(pR->Left) + Number(pR->Right) + 1;
        return pR;
    }

    static TreeNode *RotateLeft(TreeNode *p) {
        TreeNode *pL = p->Right;
        p->Right = pL->Left;
        pL->Left = p;
        p->Height = max(Height(p->Left), Height(p->Right)) + 1;
        p->Number = Number(p->Left) + Number(p->Right) + 1;
        pL->Height = max(Height(pL->Left), Height(pL->Right)) + 1;
        pL->Number = Number(pL->Left) + Number(pL->Right) + 1;
        return pL;
    }

    static TreeNode *Balance(TreeNode *p) {
        p->Height = max(Height(p->Left), Height(p->Right)) + 1;
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

    TreeNode *InsertAndGetPos(TreeNode *root, int key, int &pos) {
        if (root == nullptr) {
            return new TreeNode(key);
        }
        ++(root->Number);
        if (compareFunction(key, root->Key)) {
            pos += Number(root->Right) + 1;
            root->Left = InsertAndGetPos(root->Left, key, pos);
        } else {
            root->Right = InsertAndGetPos(root->Right, key, pos);
        }
        return Balance(root);
    }

    TreeNode *FindMin(TreeNode *p) {
        return p->Left == nullptr ? p : FindMin(p->Left);
    }

    TreeNode *RemoveMin(TreeNode *p) {
        if (p->Left == nullptr)
            return p->Right;
        p->Left = RemoveMin(p->Left);
        --p->Number;
        return Balance(p);
    }

    TreeNode *Remove(TreeNode *p, int position) {
        if (p == nullptr)
            return nullptr;
        if (position >= p->Number)
            return p;

        int sum = 0;
        stack<TreeNode *> nodes;

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
                TreeNode *left = p->Left;
                TreeNode *right = p->Right;
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
                    TreeNode *min = FindMin(right);
                    min->Right = RemoveMin(right);
                    min->Left = left;
                    p = Balance(min);
                }
                break;
            }
        }
        TreeNode *p1;
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

bool Compare(int a, int b) {
    return a < b;
}

int main() {
    AVLTree avlTree(Compare);
    int n;
    cin >> n;
    vector<int> result;
    int key;
    int position;
    int operation;
    for (int i = 0; i < n; ++i) {
        cin >> operation;
        if (operation == 1) {
            position = 0;
            cin >> key;
            avlTree.InsertAndGetPos(key, position);
            result.push_back(position);
        } else if (operation == 2) {
            cin >> key;
            avlTree.Remove(key);
        }
    }
    for (int i: result) {
        cout << i << endl;
    }

    return 0;
}
