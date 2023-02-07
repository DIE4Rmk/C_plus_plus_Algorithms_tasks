#include <iostream>
#include <algorithm>
#include <vector>
/*
 * Counting sort.
 */
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, mx = -10e7;
    std::cin >> n;
    std::vector<int> vec(n + 1, 0);
    std::vector<int> cnt(10e6, 0);
    for (int i = 0; i < n; ++i) {
        int input;
        std::cin >> input;
        if (input > mx) {
            mx = input;
        }
        vec[i] = input;
        cnt[input]++;
    }
    for (int i = 1; i <= mx; ++i) {
        cnt[i] += cnt[i - 1];
    }
    std::vector<int> outp(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        outp[cnt[vec[i]] - 1] = vec[i];
        --cnt[vec[i]];
    }
    for (int i = 0; i < n; ++i) {
        std::cout << outp[i] << " ";
    }
    return 0;
}
