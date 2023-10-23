#include <iostream>

using namespace std;

/*На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0.
Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий).
Один ящик можно вложить в другой, если его можно перевернуть так,
что размеры одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим осям.
Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
Для сортировки точек реализуйте алгоритм сортировки вставками.
Максимальное кол-во 10000.*/

struct Box {
    int id;
    int width, height, depth;

    [[nodiscard]] bool canContain(const Box& other) const {
        return (width < other.width && height < other.height && depth < other.depth) ||
               (width < other.width && height < other.depth && depth < other.height) ||
               (width < other.height && height < other.width && depth < other.depth) ||
               (width < other.height && height < other.depth && depth < other.width) ||
               (width < other.depth && height < other.width && depth < other.height) ||
               (width < other.depth && height < other.height && depth < other.width);
    }
};

void insertionSort(Box boxes[], int n) {
    for (int i = 1; i < n; ++i) {
        Box key = boxes[i];
        int j = i - 1;

        while (j >= 0 && !key.canContain(boxes[j])) {
            boxes[j + 1] = boxes[j];
            j = j - 1;
        }
        boxes[j + 1] = key;
    }
}

int main() {
    int n;
    cin >> n;
    Box boxes[10000];

    for (int i = 0; i < n; ++i) {
        boxes[i].id = i;
        cin >> boxes[i].width >> boxes[i].height >> boxes[i].depth;
    }

    insertionSort(boxes, n);

    int sequence[10000];
    sequence[0] = boxes[0].id;
    int currentIdx = 0;

    for (int i = 1; i < n; ++i) {
        if (boxes[i].canContain(boxes[currentIdx])) {
            sequence[i] = boxes[i].id;
            currentIdx = i;
        } else {
            sequence[i] = boxes[currentIdx].id;
        }
    }

    for (int i = n-1; i >= 0; --i) {
        cout << sequence[i] << " ";
    }
    cout << endl;

    return 0;
}
