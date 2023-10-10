#include <iostream>

using namespace std;

int bin_search(const int *A, int size, int elem) {
    int result = -1;
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (A[mid] == elem) {
            result = mid;
            break;
        } else if (A[mid] < elem) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}


int main() {
    int A[10000];
    fill_n(A, 10000, 0);
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    int elem = 0;
    cin >> elem;
    cout << bin_search(A, n, elem);
    return 0;
}
