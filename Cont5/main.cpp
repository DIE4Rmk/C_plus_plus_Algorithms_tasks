#include <iostream>

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
    int arr[x.size()][y.size()];
    for (int i = 0; i < y.size(); ++i) {
        for (int j = 0; j < x.size(); ++j) {
            arr[j][i] = 0;
        }
    }
    int mx = 0;
    for (int i = 0; i < y.size(); ++i) {
        for (int j = 0; j < x.size(); ++j) {
            if (x[j] == y[i]) {
                arr[j][i]++;
                if (j > 0 && i > 0) {
                    arr[j][i] += arr[j - 1][i - 1];
                }
            } else {
                if (i > 0) {
                    if (arr[j][i - 1] > arr[j][i]) {
                        arr[j][i] = arr[j][i - 1];
                    }
                }
                if (j > 0) {
                    if (arr[j - 1][i] > arr[j][i]) {
                        arr[j][i] = arr[j - 1][i];
                    }
                }
            }
            if (mx < arr[j][i]) {
                mx = arr[j][i];
            }
        }
    }
    std::cout << mx;
    return 0;
}
