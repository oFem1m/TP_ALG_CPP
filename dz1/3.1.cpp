#include <iostream>
#include <cassert>

using namespace std;

class Queue {
public:
    explicit Queue(int size);

    ~Queue() { delete[] buffer; }

    // Добавление элемента в начало
    void push_front(int a);

    // Удаление первого элемента
    int pop_front();

    // Добавление элемента в конец
    void push_back(int a);

    // Удаление последнего элемента
    int pop_back();

    // Проверка на пустоту.
    [[nodiscard]] bool IsEmpty() const { return head == tail; }

private:
    int *buffer;
    int bufferSize;
    int head;
    int tail;
};

Queue::Queue(int size) :
        bufferSize(size),
        head(0),
        tail(0) {
    buffer = new int[bufferSize];
}

// Добавление элемента в начало
void Queue::push_front(int a) {
    assert((tail + 1) % bufferSize != head);
    head = (head - 1 + bufferSize) % bufferSize;
    buffer[head] = a;
}

// Извлечение первого элемента
int Queue::pop_front() {
    assert(head != tail);
    int result = buffer[head];
    head = (head + 1) % bufferSize;

    return result;
}

// Добавление элемента в конец
void Queue::push_back(int a) {
    assert((tail + 1) % bufferSize != head);
    buffer[tail] = a;
    tail = (tail + 1) % bufferSize;
}

// Извлечение последнего элемента
int Queue::pop_back() {
    assert(head != tail);
    tail = (tail - 1 + bufferSize) % bufferSize;
    int result = buffer[tail];

    return result;
}

int main() {
    Queue Q(1000001);
    int NumCommands = 0;
    cin >> NumCommands;
    bool isCorrect = true;
    for (int i = 0; i < NumCommands; ++i) {
        int command = 0, value = 0;
        cin >> command >> value;
        switch (command) {
            case 1:
                Q.push_front(value);
                break;
            case 2: {
                int element = (Q.IsEmpty()) ? -1 : Q.pop_front();
                if (element != value) isCorrect = false;
                break;
            }
            case 3:
                Q.push_back(value);
                break;
            case 4: {
                int element = (Q.IsEmpty()) ? -1 : Q.pop_back();
                if (element != value) isCorrect = false;
                break;
            }
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
