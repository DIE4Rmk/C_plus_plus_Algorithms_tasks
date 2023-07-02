#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <string>
#include <algorithm>

void coder(std::string input, std::vector<int> *code) {
    std::unordered_map<std::string, int> alph;
    for (int i = 0; i < 128; ++i) {
        char arr[] = {static_cast<char>(i)};
        std::string ch(arr, 1);
        alph[ch] = i;
    }

    std::string couple;
    couple += input[0];

    int tick = 128;
    for (int iter = 0; iter < input.length(); ++iter) {
        std::string string;
        if (iter != input.length() - 1) {
            string += input[iter + 1];
        }

        if (alph.find(couple + string) == alph.end()) {
            code->push_back(alph[couple]);
            alph[couple + string] = tick;
            ++tick;
            couple = string;
        } else {
            couple += string;
        }
    }
    code->push_back(alph[couple]);
    std::cout << alph.size() - 127 << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::getline(std::cin, input);

    std::vector<int> code;
    coder(input, &code);
    std::copy(code.begin(), code.end(), std::ostream_iterator<int>(std::cout, " "));
}
