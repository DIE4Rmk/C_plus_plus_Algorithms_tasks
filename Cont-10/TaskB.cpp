#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

std::string decoding(std::vector<int> message) {
    std::unordered_map<int, std::string> alph;
    for (int i = 0; i < 128; ++i) {
        char arr[] = {static_cast<char>(i)};
        std::string ch(arr, 1);
        alph[i] = ch;
    }

    std::string result;
    int previous = message[0];

    std::string string = alph[previous];
    std::string couple;
    couple += string[0];
    result += couple;

    int tick = 128;
    for (int iter = 0; iter < message.size() - 1; ++iter) {
        int position = message[iter + 1];
        if (alph.find(position) == alph.end()) {
            string = alph[previous];
            string += couple;
        } else {
            string = alph[position];
        }
        result += string;

        couple = "";
        couple += string[0];
        alph[tick++] = alph[previous] + couple;
        previous = position;
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_codes;
    std::cin >> count_codes;

    std::vector<int> code;
    for (int i = 0; i < count_codes; ++i) {
        int input;
        std::cin >> input;
        code.push_back(input);
    }

    std::cout << decoding(code);
}
