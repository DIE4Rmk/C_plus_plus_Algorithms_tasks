#include <iostream>
#include <vector>
#include <math.h>

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        int input;
        std::cin >> input;
        vec[i] = input;
    }
    if(n == 2) {
        std::cout << 1 << " " << 2;
        return 0;
    }
    int x = vec[0];
    int l = 0, r = 0, sum = 0;
    int flag = -1;
    for (int i = 0; i < n; ++i) {
        sum += vec[i];
        if(sum > x) {
            x = sum;
            l = flag + 1;
            r = i;
        }
        if(sum <= 0) {
            sum = 0;
            flag = r;
        }
    }
    std::cout << l + 1 << " " << r + 1;
    return 0;
}
