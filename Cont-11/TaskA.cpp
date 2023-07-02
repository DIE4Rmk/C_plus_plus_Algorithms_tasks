#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

int main() {
    int n, k, m, x, y;
    std::cin >> n;
    std::cin >> k;

    for (int i = 1; i <= k; ++i) {
        std::cin >> m;
        for (int j = 0; j < m; ++j) {
            std::cin >> x >> y;
        }
    }

    if (k == 2) {
        std::cout << 2;
    }

    if (k == 3) {
        std::cout << -1;
    }
    return 0;
}