#include <iostream>
#include <vector>
#include <math.h>

// Supported by https://peltorator.ru/posts/prefix_sums/

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int16_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int16_t>> vec(n, std::vector<int16_t>(m));
    for (int16_t i = 0; i < n; ++i) {
        for (int16_t j = 0; j < m; ++j) {
            int16_t input;
            std::cin >> input;
            vec[i][j] = input;
        }
    }
    std::vector<std::vector<int>> pref(n + 1, std::vector<int>(m + 1, 0));
    for (int16_t i = 0; i < n; ++i) {
        for (int16_t j = 0; j < m; ++j) {
            pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + vec[i][j];
        }
    }
    vec.clear();
    int mx = 1;
    for (int y1 = 1; y1 < n; ++y1) {
        for (int x1 = 1; x1 < m; ++x1) {
            int x2 = x1 + mx;
            int y2 = y1 + mx;
            if (x2 < m + 1 && y2 < n + 1) {
                int sum = pref[y2][x2] + pref[y1 - 1][x1 - 1] - pref[y1 - 1][x2] - pref[y2][x1 - 1];
                if (sum == (x2 - x1 + 1) * (x2 - x1 + 1)) {
                    mx = x2 - x1 + 1;
                    --x1;
                }
            }
        }
    }
    pref.clear();
    std::cout << mx;
    return 0;
}
