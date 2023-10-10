#include <iostream>

using namespace std;

int find_bit(int number, int bit) {
    int shift = number >> bit;
    return shift & 1;
}

int main() {
    int number = 0, bit = 0;
    cin >> number >> bit;
    cout << find_bit(number, bit) << endl;
    return 0;
}
