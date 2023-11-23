#include <iostream>
#include <vector>
#include <string>

class DynamicHashSet {
private:
    int size;
    int count;
    std::vector<std::string> table;

    int hashFunction(const std::string& key) {
        int hashValue = 0;
        int a = 31;
        for (char ch : key) {
            hashValue = (a * hashValue + static_cast<int>(ch)) % size;
        }
        return hashValue;
    }

    int doubleHashing(const std::string& key) {
        int hashValue = hashFunction(key);
        return 1 + (hashValue % (size - 1));
    }

    void rehash() {
        std::vector<std::string> oldTable = table;
        size *= 2;
        table.assign(size, "");
        count = 0;

        for (const std::string& item : oldTable) {
            if (!item.empty()) {
                add(item);
            }
        }
    }

public:
    DynamicHashSet() : size(8), count(0), table(size, "") {}

    std::string add(const std::string& key) {
        if (count >= 3 * size / 4) {
            rehash();
        }

        int initialHash = hashFunction(key);
        int step = doubleHashing(key);

        while (!table[initialHash].empty()) {
            if (table[initialHash] == key) {
                return "FAIL";
            }

            initialHash = (initialHash + step) % size;
        }

        table[initialHash] = key;
        count++;
        return "OK";
    }

    std::string remove(const std::string& key) {
        int initialHash = hashFunction(key);
        int step = doubleHashing(key);

        while (!table[initialHash].empty()) {
            if (table[initialHash] == key) {
                table[initialHash] = "";
                count--;
                return "OK";
            }

            initialHash = (initialHash + step) % size;
        }

        return "FAIL";
    }

    std::string contains(const std::string& key) {
        int initialHash = hashFunction(key);
        int step = doubleHashing(key);

        while (!table[initialHash].empty()) {
            if (table[initialHash] == key) {
                return "OK";
            }

            initialHash = (initialHash + step) % size;
        }

        return "FAIL";
    }
};

int main() {
    DynamicHashSet hashSet;

    char operation;
    std::string key;

    while (std::cin >> operation >> key) {
        if (operation == '+') {
            std::cout << hashSet.add(key) << std::endl;
        } else if (operation == '-') {
            std::cout << hashSet.remove(key) << std::endl;
        } else if (operation == '?') {
            std::cout << hashSet.contains(key) << std::endl;
        }
    }

    return 0;
}
