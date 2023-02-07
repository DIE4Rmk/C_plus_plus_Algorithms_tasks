#include <iostream>
#include <algorithm>
#include <vector>

struct Drone {
    unsigned int id;
    unsigned int weight;
};

/*
 * Radix sort по убыванию для структуры.
 */
void countSort(std::vector<Drone> &vec, int64_t e, int64_t n) {
    std::vector<int> cnt(10);
    for (int64_t i = 0; i < n; ++i) {
        cnt[(vec[i].weight / e) % 10]++;
    }
    for (int64_t i = 8; i >= 0; --i) {
        cnt[i] += cnt[i + 1];
    }
    std::vector<Drone> outp(n);
    for (int64_t i = n - 1; i >= 0; --i) {
        outp[cnt[(vec[i].weight / e) % 10] - 1] = vec[i];
        --cnt[(vec[i].weight / e) % 10];
    }
    int k = 0;
    for (int64_t i = 0; i < n; ++i) {
        vec[i] = outp[i];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t n;
    std::cin >> n;
    std::vector<Drone> drones(n);
    Drone mx = {0, 0};
    for (int i = 0; i < n; ++i) {
        unsigned int curr_id;
        unsigned int w;
        std::cin >> curr_id >> w;
        drones[i].id = curr_id;
        drones[i].weight = w;
        if (w > mx.weight) {
            mx.id = curr_id;
            mx.weight = w;
        }
    }
    for (int64_t e = 1; mx.weight / e > 0; e *= 10) {
        countSort(drones, e, n);
    }
    for (auto &i : drones) {
        std::cout << i.id << " " << i.weight << std::endl;
    }
}