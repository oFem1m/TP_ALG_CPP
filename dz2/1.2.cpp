#include <iostream>
#include <vector>

using namespace std;

/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
принадлежности данной строки множеству.

Для разрешения коллизий используйте двойное хеширование.

Требования: В таблице запрещено хранение указателей на описатель элемента.

Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей
за ним через пробел строки, над которой проводится операция.
Тип операции – один из трех символов:
    +  означает добавление данной строки в множество;
    -  означает удаление  строки из множества;
    ?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
 При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.

Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того,
встречается ли данное слово в нашем множестве.
*/

struct HashTableNode {
    string key;
};

class HashTable {
private:
    vector<HashTableNode> table;
    vector<bool> deleted;
    float tableSize;

    // Хеш-функция строки методом Горнера.
    int hashFunction1(const string &key) {
        int hashValue = 0;
        for (char c: key)
            hashValue = hashValue * 137 + c;
        return hashValue;
    }

    // Вторая хеш-функция для двойного хеширования.
    int hashFunction2(const string &key) {
        int hashValue = 5;
        for (int i = 0; i < key.size(); i++)
            hashValue += (key[i] + i) * 257;
        return (2 * hashValue) + 1;
    }

    void rehash() {
        vector<HashTableNode> newTable(2 * table.size());
        vector<bool> newDeleted(2 * table.size(), false);

        for (int i = 0; i < table.size(); i++) {
            if (!table[i].key.empty() && !deleted[i]) {
                int index = hashFunction1(table[i].key) % newTable.size();
                int step = hashFunction2(table[i].key) % newTable.size();

                while (!newTable[index].key.empty()) {
                    index = (index + step) % newTable.size();
                }

                newTable[index] = table[i];
            }
        }

        table = std::move(newTable);
        deleted = std::move(newDeleted);
    }

public:
    explicit HashTable(size_t size) : table(size), tableSize(0), deleted(size, false) {}

    ~HashTable() {
        table.clear();
        deleted.clear();
    }

    bool insert(const HashTableNode &element) {
        if (tableSize / float(table.size()) >= 0.75)
            rehash();

        int index = hashFunction1(element.key) % table.size();
        int step = hashFunction2(element.key) % table.size();
        int DeletedItem = 0;
        for (int i = 0; i < table.size(); i++) {
            if (table[index].key == element.key && !deleted[index])
                return false;

            if (deleted[index]) {
                DeletedItem = index;
                for (int j = 0; j < table.size(); j++) {
                    index = (index + step) % int(table.size());
                    if (table[index].key == element.key && !deleted[index])
                        return false;
                }
                table[DeletedItem] = element;
                deleted[DeletedItem] = false;
                tableSize++;
                return true;
            }

            if (table[index].key.empty()) {
                table[index] = element;
                deleted[index] = false;
                tableSize++;
                return true;
            }
            index = (index + step) % table.size();
        }
        return false;
    }

    bool search(const HashTableNode &element) {
        int index = hashFunction1(element.key) % table.size();
        int step = hashFunction2(element.key) % table.size();
        for (int i = 0; i < table.size(); i++) {
            if (!table[index].key.empty() && table[index].key == element.key && !deleted[index])
                return true;

            if (table[index].key.empty())
                return false;

            index = (index + step) % table.size();
        }
        return false;
    }

    bool remove(const HashTableNode &element) {
        int index = hashFunction1(element.key) % table.size();
        int step = hashFunction2(element.key) % table.size();
        for (int i = 0; i < table.size(); i++) {
            if (!table[index].key.empty() && table[index].key == element.key && !deleted[index]) {
                deleted[index] = true;
                tableSize--;
                return true;
            }
            if (table[index].key.empty())
                return false;

            index = (index + step) % table.size();
        }
        return false;
    }
};

int main() {
    HashTable hashTable(8);

    char operation;
    HashTableNode element;

    while (cin >> operation >> element.key) {
        bool result;
        switch (operation) {
            case '+':
                result = hashTable.insert(element);
                break;
            case '-':
                result = hashTable.remove(element);
                break;
            case '?':
                result = hashTable.search(element);
                break;
            default:
                return 1;
        }
        if (result) {
            cout << "OK" << endl;
        } else {
            cout << "FAIL" << endl;
        }
    }

    return 0;
}
