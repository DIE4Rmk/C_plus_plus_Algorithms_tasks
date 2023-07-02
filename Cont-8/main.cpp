#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Task D Damerau-Levenshtein distance
int wagner(std::string frst, std::string sec) {
    if (frst.empty()) {
        return static_cast<int>(sec.size());
    }
    if (sec.empty()) {
        return static_cast<int>(frst.size());
    }
    int dist[frst.size() + 1][sec.size() + 1];
    for (size_t i = 0; i <= frst.size(); ++i) {
        for (size_t j = 0; j <= sec.size(); ++j) {
            dist[i][j] = 0;
        }
    }
    for (size_t i = 0; i <= frst.size(); ++i) {
        dist[i][0] = static_cast<int>(i);
    }
    for (size_t i = 0; i <= sec.size(); ++i) {
        dist[0][i] = static_cast<int>(i);
    }
    for (size_t it_i = 1; it_i <= sec.size(); ++it_i) {
        for (size_t it_j = 1; it_j <= frst.size(); ++it_j) {
            if (it_j > 1 && it_i > 1 && frst[it_j - 1] == sec[it_i - 2] &&
                frst[it_j - 2] == sec[it_i - 1]) {
                if (frst[it_j - 1] == sec[it_i - 1]) {
                    dist[it_j][it_i] =
                            std::min(std::min(dist[it_j - 2][it_i - 2] + 1, dist[it_j - 1][it_i] + 1),
                                     std::min(dist[it_j][it_i - 1] + 1, dist[it_j - 1][it_i - 1]));
                } else {
                    dist[it_j][it_i] =
                            std::min(std::min(dist[it_j - 2][it_i - 2] + 1,
                                              dist[it_j - 1][it_i] + 1),
                                     std::min(dist[it_j][it_i - 1] + 1, dist[it_j - 1][it_i - 1] + 1));
                }
            } else {
                if (frst[it_j - 1] == sec[it_i - 1]) {
                    dist[it_j][it_i] =
                            std::min(std::min(dist[it_j - 1][it_i] + 1, dist[it_j][it_i - 1] + 1),
                                     dist[it_j - 1][it_i - 1]);
                } else {
                    dist[it_j][it_i] =
                            std::min(std::min(dist[it_j - 1][it_i] + 1, dist[it_j][it_i - 1] + 1),
                                     dist[it_j - 1][it_i - 1] + 1);
                }
            }
        }
    }
    return dist[frst.size()][sec.size()];
}

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string string_amount;
    std::getline(std::cin, string_amount);
    int counter = stoi(string_amount);
    for (int iter = 0; iter < counter; ++iter) {
        std::string frst, sec;
        std::getline(std::cin, frst);
        std::getline(std::cin, sec);

        std::cout << std::min(wagner(frst, sec), wagner(sec, frst)) << " ";
    }
}