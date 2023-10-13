#include <iostream>

using namespace std;

/*Вернуть значение бита в числе N по его номеру K.*/

int find_bit(int number, int bit) {
    int shift = number >> bit;
    return shift & 1;
}

int main() {
    int N = 0, K = 0;
    cin >> N >> K;
    cout << find_bit(N, K) << endl;
    return 0;
}
