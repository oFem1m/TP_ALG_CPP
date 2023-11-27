#include <iostream>
#include <unordered_set>

using namespace std;

/*
Нужно кастомизировать std::unordered_set для операций со структурой данных
struct Node {
std::string product_name;
int color;
int size;
};
Формат ввода
Каждая строка входных данных задает одну операцию над множеством.
Запись операции состоит из типа операции и следующей за ним через пробел тройки значений структуры,
над которой проводится операция.
Тип операции – один из трех символов:
+ означает добавление данной строки в множество;
- означает удаление строки из множества;
? означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат вывода
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того,
встречается ли данные в нашем множестве.
*/

struct Node {
    string product_name;
    int color;
    int size;

    // Перегрузка оператора ==
    bool operator==(const Node& other) const {
        return product_name == other.product_name && color == other.color && size == other.size;
    }
};

// Специализация std::hash для структуры Node
namespace std {
    template <>
    struct hash<Node> {
        size_t operator()(const Node& node) const {
            size_t hashValue = hash<string>()(node.product_name);
            hashValue = hash<int>()(node.color) + hashValue * 37;
            hashValue = hash<int>()(node.size) + hashValue * 37;
            return hashValue;
        }
    };
}

int main() {
    unordered_set<Node> nodes;

    char operation;
    Node node;

    while (cin >> operation >> node.product_name >> node.color >> node.size) {
        if (operation == '+') {
            auto result = nodes.insert(node);
            cout << (result.second ? "OK" : "FAIL") << endl;
        } else if (operation == '-') {
            size_t erased = nodes.erase(node);
            cout << (erased > 0 ? "OK" : "FAIL") << endl;
        } else if (operation == '?') {
            auto it = nodes.find(node);
            cout << (it != nodes.end() ? "OK" : "FAIL") << endl;
        }
    }

    return 0;
}
