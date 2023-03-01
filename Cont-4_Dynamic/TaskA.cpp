#include <iostream>
#include <vector>
#include <algorithm>

#pragma GCC optimize("-align-loops")

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> vec;

    for (int i = 0; i < n; ++i) {
        int input;
        std::cin >> input;
        vec.emplace_back(input, 0);
        std::cin >> input;
        vec.emplace_back(input, 2);
    }
    for (int i = 0; i < m; ++i) {
        int input;
        std::cin >> input;
        vec.emplace_back(input, 1);
    }
    std::sort(vec.begin(), vec.end());
    int counter = 0;
    for (auto &i : vec) {
        switch (i.second) {
            case 0:
                counter++;
                break;
            case 1:
                std::cout << counter << " ";
                break;
            case 2:
                counter--;
                break;
        }
    }
    return 0;
}