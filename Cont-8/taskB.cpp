#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Task C Wagner Fisher
int chvkWagner(std::string frst, std::string sec) {
    std::vector<std::vector<int>> dist(frst.size() + 1, std::vector<int>(sec.size() + 1, 0));

    for (size_t i = 0; i < frst.size() + 1; ++i) {
        dist[i][0] = static_cast<int>(i);
    }
    for (size_t i = 0; i < sec.size() + 1; ++i) {
        dist[0][i] = static_cast<int>(i);
    }

    for (size_t it_i = 1; it_i < sec.size() + 1; ++it_i) {
        for (size_t it_j = 1; it_j < frst.size() + 1; ++it_j) {
            if (frst[it_j - 1] == sec[it_i - 1]) {
                dist[it_j][it_i] = dist[it_j - 1][it_i - 1];
            } else {
                int min = std::min(dist[it_j][it_i - 1] + 1, dist[it_j - 1][it_i - 1] + 1);
                dist[it_j][it_i] = std::min(1 + dist[it_j - 1][it_i], min);
            }
        }
    }
    return dist[frst.size()][sec.size()];
}

int main() {
    std::string frst, sec;
    std::cin >> frst >> sec;
    std::cout << chvkWagner(frst, sec);
    return 0;
}