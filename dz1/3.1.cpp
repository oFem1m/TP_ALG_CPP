#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

/*Реализовать очередь с динамическим зацикленным буфером (на основе динамического массива).

Формат входных данных:
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных,
то ожидается “-1”.

Формат выходных данных:
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось,
то напечатать NO.
*/

class Queue {
public:
    explicit Queue(int size);

    ~Queue() { delete[] buffer; }

    // Удаление первого элемента
    int pop_front();

    // Добавление элемента в конец
    void push_back(int a);

    // Проверка на пустоту.
    [[nodiscard]] bool IsEmpty() const { return head == tail; }

private:
    int *buffer;
    int bufferSize;
    int head;
    int tail;

    // Увеличение буфера
    void grow();
};

// Инициализация
Queue::Queue(int size) :
        bufferSize(size),
        head(0),
        tail(0) {
    buffer = new int[bufferSize];
}

// Извлечение первого элемента
int Queue::pop_front() {
    assert(head != tail);
    int result = buffer[head];
    ++head;
    return result;
}

// Добавление элемента в конец
void Queue::push_back(int a) {
    if (tail >= bufferSize) {
        grow();
    }
    buffer[tail] = a;
    ++tail;
}

// Увеличение буфера
void Queue::grow() {
    int newBufferSize = max(bufferSize * 2, 1);
    int* newBuffer = new int[newBufferSize];
    copy(buffer + head, buffer + tail, newBuffer);
    tail -= head;
    head = 0;
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

int main() {
    Queue Q(1);
    int NumCommands = 0;
    cin >> NumCommands;
    bool isCorrect = true;
    for (int i = 0; i < NumCommands; ++i) {
        int command = 0, value = 0;
        cin >> command >> value;
        switch (command) {
            case 2: {
                int element = (Q.IsEmpty()) ? -1 : Q.pop_front();
                if (element != value) isCorrect = false;
                break;
            }
            case 3:
                Q.push_back(value);
                break;
            default:
                break;
        }

    }
    if (isCorrect)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
