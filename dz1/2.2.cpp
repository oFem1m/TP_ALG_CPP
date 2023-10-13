#include <iostream>

using namespace std;

/*Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают,
 а на интервале [m, n-1] строго убывают. Найти m за O(log m).*/

int find_m(const int *A, int n) {
    int low = 0;
    int high = n - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        if (A[mid] < A[mid + 1]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}


int main() {
    int A[10000];
    fill_n(A, 10000, 0);
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    cout << find_m(A, n);
    return 0;
}
