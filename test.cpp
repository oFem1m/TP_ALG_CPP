#include <iostream>
#include <vector>


using namespace ::std;
const float MAX_ALPHA = 0.75;

struct HashTableNode {
    string key;
};

class HashTable {
private:
    float realSize = 0;
    vector<HashTableNode> table;
    vector<bool> deleted;

    int hash1(const std::string &key) {
        int hash = 0;
        for (char i : key) {
            hash = hash * 137 + i;
        }
        return hash;
    }

    int hash2(const std::string &key) {
        int hash = 5;
        for (int i = 0; i < key.size(); i++) {
            hash += (key[i] + i) * 257;
        }
        return (2 * hash) + 1; // Возвращаем результат, который всегда больше нуля
    }
    void rehash() {
        vector<HashTableNode> NewTable(2 * table.size());
        vector<bool> NewDeleted(2 * deleted.size(), false);
        for (int i = 0; i < table.size(); i++) {
            if (!table[i].key.empty() && !deleted[i]) {
                HashTableNode elem = table[i];
                int x = hash1(elem.key) % NewTable.size();
                int y = hash2(elem.key) % NewTable.size();
                for (int j = 0; j < NewTable.size(); j++) {
                    if (NewTable[x].key == elem.key) {
                        break;
                    }
                    if (NewTable[x].key.empty()) {
                        NewTable[x] = elem;
                        break;
                    }
                    x = (x + y) % NewTable.size();
                }
            }
        }
        table = NewTable;
        deleted = NewDeleted;
    }

public:
    explicit HashTable(size_t size) : table(size), deleted(size, false) {}

    ~HashTable() {
        table.clear();
        deleted.clear();
    }

    bool Add(const HashTableNode& elem) {
        float loadFactor = realSize / float(table.size());
        if (loadFactor >= MAX_ALPHA) {
            rehash();
        }
        // за x берём результат первой хеш-функции
        int x = hash1(elem.key) % table.size();
        // за y берём результат второй хеш-функции
        int y = hash2(elem.key) % table.size();
        // для сохранения индекса элемента, если он удалён
        int DeletedItem = 0;
        for (int i = 0; i < table.size(); i++) {
            if (table[x].key == elem.key && !deleted[x]) {
                return false;
            }
            if (deleted[x]) {
                DeletedItem = x;
                for (int j = 0; j < table.size(); j++) {
                    x = (x + y) % table.size();
                    if (table[x].key == elem.key && !deleted[x]) {
                        return false;
                    }
                }
                table[DeletedItem] = elem;
                deleted[DeletedItem] = false;
                realSize++;
                return true;
            }
            if (table[x].key.empty()) {
                table[x] = elem;
                deleted[x] = false;
                realSize++;
                return true;
            }
            x = (x + y) % table.size();
        }
        return false;
    }


    bool Has(const HashTableNode elem) {
        int x = hash1(elem.key) % table.size();
        int y = hash2(elem.key) % table.size();
        for (int i = 0; i < table.size(); i++) {
            if (!table[x].key.empty()) {
                if (table[x].key == elem.key && !deleted[x]) {
                    return true;
                }
            } else {
                return false;
            }
            x = (x + y) % table.size();
        }
        return false;
    }

    bool Delete(const HashTableNode& elem) {
        int x = hash1(elem.key) % table.size();
        int y = hash2(elem.key) % table.size();
        for (int i = 0; i < table.size(); i++) {
            if (!table[x].key.empty()) {
                if (table[x].key == elem.key && !deleted[x]) {
                    deleted[x] = true;
                    realSize--;
                    return true;
                }
            } else {
                return false;
            }
            x = (x + y) % table.size();
        }
        return false;
    }
};

int main() {
    HashTable table(8);

    char op;
    string key;
    HashTableNode node;
    while (std::cin >> op >> node.key) {
        switch (op) {
            case '?': {
                std::cout << (table.Has(node) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '+': {
                cout << (table.Add(node) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-': {
                std::cout << (table.Delete(node) ? "OK" : "FAIL") << std::endl;
                break;
            }
            default:
                return 1;
        }
    }
    return 0;
}
