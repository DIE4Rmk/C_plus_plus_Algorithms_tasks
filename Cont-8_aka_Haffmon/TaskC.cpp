#include <iostream>
#include <cmath>
#include <string>
#include <vector>

int getSizeLenght(int data_len) {

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<int> vec(10e6);

    std::string data;
    std::getline(std::cin, data);
    size_t data.length() = data.length();
    int size_arr = 0;
    while (pow(2, size_arr) < static_cast<int>(data.length()) + size_arr + 1) {
        ++size_arr;
    }

    for (int i = 1; i <= data.length(); ++i) {
        if (data[i - 1] == '0') {
            vec[i] = 0;
        } else {
            vec[i] = 1;
        }
    }

    std::vector<int> ham_code(data.length() + size_arr + 1);
    int j = 0;
    int k = 1;
    for (int i = 1; i <= data.length() + size_arr; ++i) {
        if (i == pow(2, j)) {
            ham_code[i] = -1;
            ++j;
        } else {
            ham_code[i] = vec[k];
            ++k;
        }
    }

    k = 0;
    for (int i = 1; i <= data.length() + size_arr; i = static_cast<int>(pow(2, k))) {
        int flag = 0;
        j = i;
        int min = 1;
        int mx = i;
        while (j <= data.length() + size_arr) {
            int x;
            for (x = j; mx >= min && x <= data.length() + size_arr; ++min, ++x) {
                if (ham_code[x] == 1) {
                    flag = flag + 1;
                }
            }

            j = x + i;
            min = 1;
        }

        if (flag % 2 == 0) {
            ham_code[i] = 0;
        } else {
            ham_code[i] = 1;
        }
        ++k;
    }

    for (int i = 1; i <= data.length() + size_arr; ++i) {
        std::cout << ham_code[i];
    }

    return 0;
}
