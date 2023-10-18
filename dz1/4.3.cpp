#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class DynamicHeap {
public:
    DynamicHeap() {
        data_ = new T[INITIAL_CAPACITY];
        capacity_ = INITIAL_CAPACITY;
        size_ = 0;
    }

    ~DynamicHeap() {
        delete[] data_;
    }

    void Insert(T item) {
        if (size_ >= capacity_) {
            // Если куча заполнена, увеличиваем ее размер
            ExpandCapacity();
        }

        data_[size_] = item;
        HeapifyUp(size_);
        size_++;
    }

    T ExtractMax() {
        if (size_ == 0) {
            throw std::out_of_range("Heap is empty");
        }

        T maxItem = data_[0];
        data_[0] = data_[size_ - 1];
        size_--;

        HeapifyDown(0);

        return maxItem;
    }

private:
    static const int INITIAL_CAPACITY = 10;
    T *data_;
    int capacity_;
    int size_;

    void ExpandCapacity() {
        int newCapacity = capacity_ * 2;
        T *newData = new T[newCapacity];

        for (int i = 0; i < size_; i++) {
            newData[i] = data_[i];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    void HeapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && data_[index] > data_[parent]) {
            std::swap(data_[index], data_[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void HeapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < size_ && data_[leftChild] > data_[largest]) {
            largest = leftChild;
        }

        if (rightChild < size_ && data_[rightChild] > data_[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            std::swap(data_[index], data_[largest]);
            HeapifyDown(largest);
        }
    }
};


int main() {

    return 0;
}
