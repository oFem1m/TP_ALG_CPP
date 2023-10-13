#include <iostream>
#include <vector>

void sort(int *arr, int l, int r) {
    for (int i = l; i < r; ++i) {
        for (int j = l; j < r - 1; ++j) {
            if (arr[j + 1] < arr[j]) {
                std::swap(arr[j + 1], arr[j]);
            }
        }
    }
}

bool is_less(const int &l, const int &r) {
    return l < r;
}

bool is_more(const int &l, const int &r) {
    return l > r;
}


void sort_cmp(int *arr, int l, int r, bool (*comp)(const int &, const int &)) {
    for (int i = l; i < r; ++i) {
        for (int j = l; j < r - 1; ++j) {
            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j + 1], arr[j]);
            }
        }
    }
}

template <class T>
void sort(T *arr, int l, int r, bool (*comp)(const T&, const T&)) {
    for (int i = l; i < r; ++i) {
        for (int j = l; j < r - 1; ++j) {
            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j + 1], arr[j]);
            }
        }
    }
}


int main() {
    std::vector<int> arr = {3, 2, 1};
    //sort_cmp(&arr[0], 0, arr.size(), is_less);
    int counter = 0;
    sort_cmp(&arr[0], 0, arr.size(), [](const int &l, const int &r) {
        return l > r;
    });
    for (int i: arr) {
        std::cout << i << " ";
    }
    return 0;
}
