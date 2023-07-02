#include <iostream>
#include <vector>
int n, m;

int64_t brr(int y, int x, std::vector<std::vector<int64_t>> &vec) {
    if(vec[y][x] > 0) {
        return vec[y][x];
    } else {
        vec[y][x] = 0;
    }
    // Right up.
    if(n - 1 > y && x > 1) {
        vec[y][x] += brr(y - 1, x + 2, vec);
    }
    // Down right
    if(x > 0 && y > 1) {
        vec[y][x] += brr(y - 1, x + 1, vec);
    }
}

int main() {
    std::cin >> n >> m;
    std::vector<std::vector<int64_t>> vec(n);
    for (int i = 0; i < n; ++i) {
        std::vector<int64_t> inp(m, -1);
        vec[i] = inp;
    }
    int64_t ans = brr(n - 1, m - 1, vec);
    return 0;
}
