#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::string x, y;
    std::getline(std::cin, x);
    std::getline(std::cin, y);
    if (x.size() > y.size()) {
        std::swap(x, y);
    }
    std::vector<std::vector<int>> arr(y.size());
    for (int i = 0; i < y.size(); ++i) {
        std::vector<int> xx(x.size(), 0);
        arr[i] = xx;
    }
    int mx = 0;
    for (int i = 0; i < y.size(); ++i) {
        for (int j = 0; j < x.size(); ++j) {
            if (x[j] == y[i]) {
                arr[i][j]++;
                if (j > 0 && i > 0) {
                    arr[i][j] += arr[i - 1][j - 1];
                }
            } else {
                if (i > 0) {
                    if (arr[i - 1][j] > arr[i][j]) {
                        arr[i][j] = arr[i - 1][j];
                    }
                }
                if (j > 0) {
                    if (arr[i][j - 1] > arr[i][j]) {
                        arr[i][j] = arr[i][j - 1];
                    }
                }
            }
            if (mx < arr[i][j]) {
                mx = arr[i][j];
            }
        }
    }
    std::cout << mx;
    return 0;
}
