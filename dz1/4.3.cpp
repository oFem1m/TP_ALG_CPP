#include <iostream>

using namespace std;

/*
В операционной системе Technux есть планировщик процессов.
Каждый процесс характеризуется:

приоритетом P
временем, которое он уже отработал t
временем, которое необходимо для завершения работы процесса T
Планировщик процессов выбирает процесс с минимальным значением P * (t + 1), выполняет его время P и
кладет обратно в очередь процессов.
Если выполняется условие t >= T, то процесс считается завершенным и удаляется из очереди.
Требуется посчитать кол-во переключений процессора.

Требования:
В качестве очереди с приоритетом нужно использовать кучу.
Куча должна быть реализована в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
*/

template <typename T, typename Compare = less<T>>
class MinHeap {
public:
    explicit MinHeap(Compare comp = Compare()) : capacity(10), size(0), compare(comp) {
        data = new T[capacity];
    }

    ~MinHeap() {
        delete[] data;
    }

    void push(const T& value) {
        if (size >= capacity) {
            increaseCapacity();
        }

        int index = size;
        data[index] = value;
        size++;

        while (index > 0 && compare(value, data[parent(index)])) {
            swap(data[index], data[parent(index)]);
            index = parent(index);
        }
    }

    T pop() {
        if (empty()) {
            throw out_of_range("Heap is empty");
        }

        T top = data[0];
        data[0] = data[size - 1];
        size--;

        int index = 0;
        while (true) {
            int left = leftChild(index);
            int right = rightChild(index);
            int smallest = index;

            if (left < size && compare(data[left], data[smallest])) {
                smallest = left;
            }
            if (right < size && compare(data[right], data[smallest])) {
                smallest = right;
            }

            if (smallest != index) {
                swap(data[index], data[smallest]);
                index = smallest;
            } else {
                break;
            }
        }

        return top;
    }

    [[nodiscard]] bool empty() const {
        return size == 0;
    }

private:
    T* data;
    size_t capacity;
    size_t size;
    Compare compare;

    void increaseCapacity() {
        T* newData = new T[capacity * 2];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity *= 2;
    }

    [[nodiscard]] int parent(int index) const {
        return (index - 1) / 2;
    }

    [[nodiscard]] int leftChild(int index) const {
        return 2 * index + 1;
    }

    [[nodiscard]] int rightChild(int index) const {
        return 2 * index + 2;
    }
};

struct Process {
    int priority;
    int time_elapsed;
    int time_required;

    bool operator<(const Process& other) const {
        return (priority * (time_elapsed + 1)) > (other.priority * (other.time_elapsed + 1));
    }
};

int main() {
    int n;
    cin >> n;

    MinHeap<Process> process_heap;

    for (int i = 0; i < n; i++) {
        int priority, time_required;
        cin >> priority >> time_required;
        process_heap.push({priority, 0, time_required});
    }

    int total_switches = 0;
    int current_time = 0;

    while (!process_heap.empty()) {
        Process current_process = process_heap.pop();
        int time_required = current_process.time_required;
        current_time += current_process.priority;
        total_switches++;

        if (current_process.time_elapsed + current_process.priority >= time_required) {
            continue;
        } else {
            current_process.time_elapsed += current_process.priority;
            process_heap.push(current_process);
        }
    }

    cout << total_switches << endl;

    return 0;
}
