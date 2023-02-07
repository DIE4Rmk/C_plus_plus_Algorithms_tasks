#include <iostream>
#include <vector>
/*
 * Task D.
 */
int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n, 0);
    for (int i = 0; i < n; ++i) {
        int input;
        std::cin >> input;
        vec[i] = input;
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int input;
        std::cin >> input;
        vec[input - 1]--;
    }
    for (int i = 0; i < n; ++i) {
        if (vec[i] < 0) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
    }
    return 0;
}