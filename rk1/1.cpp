#include <iostream>

using namespace std;

/*Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1].
На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента k в массиве A,
если он там присутствует, либо вернуть позицию, куда его следовало бы вставить, чтобы массив остался отсортированным.

Требование: сложность O(logN)

Формат ввода
В первой строчке записано число n – размерность массива A.
Во второй строчке перечислены элементы массива A. В третьей строчке записано значение k.

Формат вывода
Целое число — позиция k в A.
*/

int binarySearch(const int A[], int n, int k) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (A[mid] == k) {
            return mid; // Найден элемент k
        } else if (A[mid] < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left; // k не найден, возвращаем позицию для вставки
}

int main() {
    int n;
    cin >> n;

    int A[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int k;
    cin >> k;

    int result = binarySearch(A, n, k);
    cout << result << endl;

    return 0;
}
