#include <iostream>
#include <string>
#include <vector>

void decode(std::vector<char> *input, int length) {
    int iterator = length - 1;
    bool even = true;
    while (iterator < input->size()) {
        int shift = 0;
        while ((iterator + shift < input->size()) && (shift < length)) {
            if (input->operator[](iterator + shift) == '1') {
                even = !even;
            }
            ++shift;
        }
        iterator += 2 * length;
    }
    if (even) {
        input->operator[](length - 1) = '0';
    } else {
        input->operator[](length - 1) = '1';
    }
}

void swapping(std::vector<char> *ans, int length) {
    if (length) {
        if (ans->operator[](length - 1) == '1') {
            ans->operator[](length - 1) = '0';
        } else {
            ans->operator[](length - 1) = '1';
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::cin >> input;

    std::vector<char> ans = std::vector<char>();
    int de = 1;
    for (int i = 0; i < input.length(); ++i) {
        if (i + 1 != de) {
            ans.push_back(input[i]);
        } else {
            de *= 2;
            continue;
        }
    }

    for (int i = 1; i <= ans.size(); i = i * 2) {
        ans.insert(ans.begin() + i - 1, '#');
    }

    for (int i = 1; i <= ans.size(); i = i * 2) {
        decode(&ans, i);
    }

    int length = 0;
    for (int i = 0; i < ans.size(); ++i) {
        if (input[i] != ans[i]) {
            length += i + 1;
        }
    }

    swapping(&ans, length);
    int degree_2 = 1;
    for (int i = 0; i < ans.size(); ++i) {
        if (i == degree_2 - 1) {
            degree_2 *= 2;
            continue;
        }
        std::cout << ans[i];
    }
    return 0;
}
