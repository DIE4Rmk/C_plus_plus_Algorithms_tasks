#include <iostream>
#include <algorithm>

const int kKkcountPlaces = 12;

void findPlacements(int *students, int max, int number, int index) {
    if (number == 0) {
        if (students[0] > kKkcountPlaces) {
            return;
        }

        std::cout << students[0];
        for (int iter = 1; iter < index; ++iter) {
            std::cout << " " << students[iter];
        }
        std::cout << std::endl;
        return;
    }

    int min = std::min(max, number);
    for (int iter = 1; iter < min + 1; ++iter) {
        students[index] = iter;
        findPlacements(students, iter, number - iter, index + 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int students[50];

    int count_students;
    std::cin >> count_students;

    findPlacements(students, count_students, count_students, 0);

    return 0;
}
