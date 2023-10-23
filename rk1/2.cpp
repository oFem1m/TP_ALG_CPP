#include <iostream>
#include <string>

using namespace std;

/*ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!

Пара слов называется стековой анаграмой, если одно слово можно получить из другого,
проведя последовательность стековых операций с его буквами (взять очередную букву исходного слова и поместить ее в стек;
взять букву из стека и добавить ее в конец выходного слова). Для заданной пары слов требуется определить,
можно ли выполнить последовательность стековых операций, переводящую первое слово во второе.
Все буквы в слове различные. Длина анаграммы ≤ 10000.

Формат ввода
Пара слов, являющихся анаграммой.

Формат вывода
YES, если последовательность стековых операций существует и NO в противном случае.*/

class DynamicStack {
public:
    DynamicStack() : capacity(10), top(-1), data(new char[capacity]) {}

    ~DynamicStack() {
        delete[] data;
    }

    void push(char value) {
        if (top == capacity - 1) {
            expand();
        }
        data[++top] = value;
    }

    void pop() {
        if (top >= 0) {
            --top;
        }
    }

    char peek() {
        if (top >= 0) {
            return data[top];
        }
        return '\0'; // Возвращаем нулевой символ, если стек пуст
    }

    [[nodiscard]] bool isEmpty() const {
        return top == -1;
    }

private:
    char* data;
    int capacity;
    int top;

    void expand() {
        int newCapacity = capacity * 2;
        char* newData = new char[newCapacity];

        for (int i = 0; i <= top; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
};

bool isStackAnagram(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) {
        return false;
    }

    DynamicStack charStack;
    int i = 0; // Индекс для word1
    int j = 0; // Индекс для word2

    while (j < word2.length()) {
        if (!charStack.isEmpty() && charStack.peek() == word2[j]) {
            charStack.pop();
            j++;
        } else if (i < word1.length()) {
            charStack.push(word1[i]);
            i++;
        } else {
            return false; // Не можем выполнить стековые операции, возвращаем false
        }
    }

    return charStack.isEmpty() && i == word1.length();
}

int main() {
    string word1, word2;
    cin >> word1 >> word2;

    if (isStackAnagram(word1, word2)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
