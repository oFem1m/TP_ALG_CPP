#include <iostream>

using namespace std;

/*Группа людей называется современниками если был такой момент, когда они могли собраться вместе.
Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников.
В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
Замечание:
Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
*/

struct Event {
    int day, month, year;
    int type;
};

bool compareEvents(const Event &e1, const Event &e2) {
    if (e1.year == e2.year) {
        if (e1.month == e2.month) {
            if (e1.day == e2.day) {
                return e1.type < e2.type;
            }
            return e1.day < e2.day;
        }
        return e1.month < e2.month;
    }
    return e1.year < e2.year;
}

int findMaxContemporaries(Event *events, int n) {
    int maxContemporaries = 0;
    int currentContemporaries = 0;

    for (int i = 0; i < n; i++) {
        if (events[i].type == 0) {
            currentContemporaries++;
        } else if (events[i].type == 1) {
            currentContemporaries--;
        }

        maxContemporaries = max(maxContemporaries, currentContemporaries);
    }

    return maxContemporaries;
}

template<typename T, typename Compare>
void mergeSort(T *arr, int left, int right, Compare comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comp);
        mergeSort(arr, mid + 1, right, comp);

        int n1 = mid - left + 1;
        int n2 = right - mid;

        T *leftArr = new T[n1];
        T *rightArr = new T[n2];

        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int i = 0; i < n2; i++)
            rightArr[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (comp(leftArr[i], rightArr[j])) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }

        delete[] leftArr;
        delete[] rightArr;
    }
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

void dec_date(int &day, int &month, int &year) {
    day--;

    if (day == 0) {
        month--;

        if (month == 0) {
            year--;
            month = 12;
        }

        day = daysInMonth(month, year);
    }
}

void add_years(int &day, int &month, int &year, int add_years) {
    year += add_years;

    if (isLeapYear(year)) {
        if (month == 2 && day == 29) {
            // Если текущая дата 29 февраля, ничего не делаем
        }
        else if (month == 2 && day > 29) {
            day = 29;
        }
    }
    else {
        if (month == 2 && day >= 29) {
            day = 28;
        }
    }
}

int full_years(int day_birth, int month_birth, int year_birth, int day_death, int month_death, int year_death) {
    int years = year_death - year_birth;

    if (month_death < month_birth || (month_death == month_birth && day_death < day_birth)) {
        years--;
    }

    return years;
}


int main() {
    int n;
    cin >> n;

    auto *events = new Event[2 * n];
    int eventIndex = 0;

    for (int i = 0; i < n; i++) {
        int day_birth, month_birth, year_birth;
        int day_death, month_death, year_death;
        cin >> day_birth >> month_birth >> year_birth
            >> day_death >> month_death >> year_death;
        if (full_years(day_birth, month_birth, year_birth, day_death, month_death, year_death) < 18) {
            events[eventIndex++] = {0, 0, 0, 2}; // 2 для исключения
            events[eventIndex++] = {0, 0, 0, 2};
            continue;
        } else if (full_years(day_birth, month_birth, year_birth, day_death, month_death, year_death) == 80) {
            day_death = day_birth;
            month_death = month_birth;
        } else if ((year_death - year_birth) > 80){
            day_death = day_birth;
            month_death = month_birth;
            year_death = year_birth;
            add_years(day_death, month_death, year_death, 80);
        }

        add_years(day_birth, month_birth, year_birth, 18);
        dec_date(day_death, month_death, year_death);
        events[eventIndex++] = {day_birth, month_birth, year_birth, 0}; // 0 = рождение
        events[eventIndex++] = {day_death, month_death, year_death, 1}; // 1 = смерть
    }

    mergeSort(events, 0, 2 * n - 1, compareEvents);

    int maxContemporaries = findMaxContemporaries(events, 2 * n);

    cout << maxContemporaries << endl;

    delete[] events;

    return 0;
}
