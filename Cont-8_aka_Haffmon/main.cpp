#include <iostream>
#include <string>
#include <vector>

void decode(std::vector<char> *input, int length) {
    int it = length - 1;
    bool flag = true;
    while (it < input->size()) {
        int curr = 0;
        while ((it + curr < input->size()) && (curr < length)) {
            if (input->operator[](it + curr) == '1') {
                flag = !flag;
            }
            ++curr;
        }
        it += 2 * length;
    }
    if (flag) {
        input->operator[](length - 1) = '0';
    } else {
        input->operator[](length - 1) = '1';
    }
}

void swapp(std::vector<char> *ans, int length) {
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

    swapp(&ans, length);
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
