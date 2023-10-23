#include <iostream>
#include <algorithm>

struct Person {
    int id, birthDay, deathDay;

    bool operator<(const Person& other) const {
        return birthDay < other.birthDay;
    }
};

template <typename T, typename Compare>
void mergeSort(T* arr, int left, int right, Compare comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, comp);
        mergeSort(arr, mid + 1, right, comp);

        int n1 = mid - left + 1;
        int n2 = right - mid;

        T* leftArr = new T[n1];
        T* rightArr = new T[n2];

        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int i = 0; i < n2; i++)
            rightArr[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (comp(leftArr[i], rightArr[j])) {
                arr[k] = leftArr[i];
                i++;
            }
            else {
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

int main() {
    int n;
    std::cin >> n;
    Person* people = new Person[n];

    for (int i = 0; i < n; i++) {
        people[i].id = i;
        std::cin >> people[i].birthDay;
        std::cin >> people[i].deathDay;
    }

    // Sort the people by birthDay using the mergeSort template
    mergeSort(people, 0, n - 1, [](const Person& a, const Person& b) {
        return a.birthDay < b.birthDay;
    });

    int maxContemporary = 0;
    int contemporary = 0;
    int currentYear = 0;

    for (int i = 0; i < n; i++) {
        const Person& person = people[i];
        if (person.birthDay > currentYear) {
            if (person.birthDay > currentYear + 80) {
                // If a person's birthDay is more than 80 years after the currentYear, skip to the next year
                currentYear = person.birthDay - 80;
            } else {
                currentYear = person.birthDay;
            }
        }

        if (person.birthDay <= currentYear && person.deathDay >= currentYear + 18) {
            int maxAllowedDeath = std::min(currentYear + 80, person.deathDay);
            contemporary++;
            currentYear = maxAllowedDeath;
        }

        maxContemporary = std::max(maxContemporary, contemporary);
    }

    std::cout << maxContemporary << std::endl;

    delete[] people;
    return 0;
}
