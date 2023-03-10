#include <iostream>
#include <vector>
#include <algorithm>

// Supported by https://peltorator.ru/posts/prefix_sums/

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int16_t n, m;
    int k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> vec;
    for (int16_t i = 0; i < n; ++i) {
        std::vector<int> v(m);
        for (int16_t j = 0; j < m; ++j) {
            std::cin >> v[j];
        }
        vec.push_back(v);
    }
    std::vector<std::vector<int64_t>> pref(n + 1, std::vector<int64_t>(m + 1, 0));
    for (int16_t i = 0; i < n; ++i) {
        for (int16_t j = 0; j < m; ++j) {
            pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + vec[i][j];
        }
    }
    int16_t x1, x2, y1, y2;
    for (int i = 0; i < k; ++i) {
        std::cin >> y1 >> x1 >> y2 >> x2;
        std::cout << (pref[y2][x2] + pref[y1 - 1][x1 - 1] - pref[y1 - 1][x2] - pref[y2][x1 - 1])
                  << "\n";
    }
    return 0;
}
