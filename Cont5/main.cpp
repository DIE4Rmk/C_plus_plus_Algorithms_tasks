#include <iostream>
#include <vector>
#include <algorithm>

void getAns(int x, int y, std::vector<int> &s, std::vector<std::vector<int>> &vec,
            std::vector<int> &ans) {
    if (vec[x][y] == 0) {
        return;
    } else if (vec[x - 1][y] == vec[x][y]) {
        getAns(x - 1, y, s, vec, ans);
    } else {
        getAns(x - 1, y - s[x - 1], s, vec, ans);
        ans.push_back(s[x - 1]);
    }
}

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n, mx;
    std::cin >> n >> mx;
    std::vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }
    std::vector<std::vector<int>> vec(n + 1);
    for (int i = 0; i <= n; ++i) {
        std::vector<int> xx(mx + 1, 0);
        vec[i] = xx;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= mx; ++j) {
            vec[i][j] = vec[i - 1][j];
            if (j >= s[i - 1] && (vec[i][j] < vec[i - 1][j - s[i - 1]] + s[i - 1])) {
                vec[i][j] = vec[i - 1][j - s[i - 1]] + s[i - 1];
            }
        }
    }
    std::vector<int> ans;
    getAns(n, mx, s, vec, ans);
    vec.clear();
    s.clear();
    uint64_t ans_sum = 0, ans_num;
    for (int an : ans) {
        ans_sum += an;
    }
    ans_num = ans.size();
    std::cout << ans_sum << std::endl;
    std::cout << ans_num << std::endl;
    for (int an : ans) {
        std::cout << an << " ";
    }
    ans.clear();
    return 0;
}
