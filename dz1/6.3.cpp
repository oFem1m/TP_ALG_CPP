#include <iostream>
#include <random>

using namespace std;

/*
Дано множество целых чисел из [0..109] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10% персентиль
медиана
90% персентиль
Требования:
К дополнительной памяти: O(n).
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition.
Рекурсия запрещена.
Решение должно поддерживать передачу функции сравнения снаружи.

Реализуйте стратегию выбора опорного элемента “случайный элемент”.
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

// Функция Partition, проход двух итераторов
template <typename T, typename Compare>
int Partition(T* arr, int low, int high, Compare compare) {
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(low, high);
    int random_pivot = distribution(generator);
    swap(arr[random_pivot], arr[high]);

    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Функция поиска k-ой порядковой статистики
template<typename T, typename Compare>
T FindKthPercentile(T* arr, int n, int k, Compare compare) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int partition_index = Partition(arr, low, high, compare);
        if (partition_index == k) {
            return arr[partition_index];
        } else if (partition_index < k) {
            low = partition_index + 1;
        } else {
            high = partition_index - 1;
        }
    }

    return -1;
}

int main() {
    int n;
    cin >> n;

    int* data = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    int k1 = static_cast<int>(n * 0.1);
    int k2 = static_cast<int>(n * 0.5);
    int k3 = static_cast<int>(n * 0.9);

    int percentile10 = FindKthPercentile(data, n, k1, less<>());
    int median = FindKthPercentile(data, n, k2, less<>());
    int percentile90 = FindKthPercentile(data, n, k3, less<>());

    cout << percentile10 << endl;
    cout << median << endl;
    cout << percentile90 << endl;

    delete[] data;

    return 0;
}
