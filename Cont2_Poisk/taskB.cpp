#include <iostream>
#include <algorithm>
#include <vector>
/*
 * Radix Sort по основанию 256.
 */
void countSort(std::vector<int64_t> &vec, int64_t e, int64_t n) {
    std::vector<int64_t> cnt(256, 0);
    for (int64_t i = 0; i < n; ++i) {
        ++cnt[(vec[i] / e) % 256];
    }
    for (int64_t i = 1; i < 256; ++i) {
        cnt[i] += cnt[i - 1];
    }
    std::vector<int64_t> outp(n, 0);
    for (int64_t i = n - 1; i >= 0; --i) {
        outp[cnt[(vec[i] / e) % 256] - 1] = vec[i];
        --cnt[(vec[i] / e) % 256];
    }
    for (int64_t i = 0; i < n; ++i) {
        vec[i] = outp[i];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t n, mx = -10e7;
    std::cin >> n;
    std::vector<int64_t> vec(n + 1, 0);

    for (int64_t i = 0; i < n; ++i) {
        int64_t input;
        std::cin >> input;
        if (input > mx) {
            mx = input;
        }
        vec[i] = input;
    }
    for (int64_t i = 1; mx / i > 0; i *= 10) {
        countSort(vec, i, n);
    }
    for (int64_t i = 0; i < n; ++i) {
        std::cout << vec[i] << " ";
    }
    return 0;
}
