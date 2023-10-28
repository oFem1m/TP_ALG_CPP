#include <iostream>

using namespace std;

/*Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 1000000.
Отсортировать массив методом MSD по битам (бинарный QuickSort).*/

// Получение i-го бита числа x
int getBit(long long x, int i) {
    return (x >> i) & 1;
}

// Функция для выполнения бинарной сортировки (MSD)
void binaryMSD(long long arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) {
        return;
    }

    int i = left;
    int j = right;

    while (i <= j) {
        while (i <= right && getBit(arr[i], bit) == 0) {
            i++;
        }

        while (j >= left && getBit(arr[j], bit) == 1) {
            j--;
        }

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    binaryMSD(arr, left, j, bit - 1);
    binaryMSD(arr, i, right, bit - 1);
}


int main() {
    int n;
    cin >> n;

    long long arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    binaryMSD(arr, 0, n - 1, 63);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
