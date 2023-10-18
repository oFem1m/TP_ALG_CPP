#include <iostream>

using namespace std;

/*Дан массив целых чисел A[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают,
 а на интервале [m, n-1] строго убывают. Найти m за O(log m).*/

int min(int a, int b){
    if (a < b) {
        return a;
    }
    return b;
}

int exponential_search(const int *A, int n){
    int border = 1;
    while ((A[border] - A[border >> 1]) >= (border - (border >> 1))) {
        border = border << 1;
        if (border >= n) break;
    }
    return border >> 1;
}


int find_m(const int *A, int low, int high) {
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
    int n;
    cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    int border = exponential_search(A, n);
    int m = find_m(A, border, min(border << 1, n - 1));
    cout << m;
    delete[] A;
    return 0;
}
