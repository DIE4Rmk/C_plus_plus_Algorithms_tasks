#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

// Task A - Optimized algo Knuta Morisa
std::vector<int> boarders(std::string input) {
    std::vector<int> bvec(input.length());
    bvec[0] = 0;
    int length = 0;
    size_t it = 1;
    while (it < input.length()) {
        if (input[it] == input[length]) {
            bvec[it++] = ++length;
        } else {
            if (length != 0) {
                length = bvec[length - 1];
            } else {
                bvec[it++] = 0;
            }
        }
    }
    return bvec;
}

std::vector<int> facets(std::string input, std::vector<int> bvec) {
    std::vector<int> fvec(input.length());
    input += "#";

    fvec[0] = 0;
    for (size_t i = 1; i < fvec.size(); ++i) {
        if (input[bvec[i]] != input[i + 1]) {
            fvec[i] = bvec[i];
        } else {
            fvec[i] = fvec[bvec[i]];
        }
    }

    return fvec;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string strdata;
    std::string strent;
    std::cin >> strent;
    std::cin >> strdata;
    std::vector<int> bvec = boarders(strent);
    std::vector<int> fvec = facets(strent, bvec);

    std::vector<int> indvec;
    size_t counter = 0, it_i = 0, it_j = 0;
    while (it_i < strdata.length()) {
        if (strdata[it_i] == strent[it_j]) {
            ++it_i;
            ++it_j;
        }

        if (it_j == strent.length()) {
            ++counter;
            indvec.push_back(it_i - it_j);
            it_j = fvec[it_j - 1];
        } else {
            if (it_i < strdata.length() && strdata[it_i] != strent[it_j]) {
                if (it_j != 0) {
                    it_j = fvec[it_j - 1];
                } else {
                    ++it_i;
                }
            }
        }
    }

    std::cout << counter << std::endl;
    for (auto &item : indvec) {
        std::cout << item << std::endl;
    }

    return 0;
}