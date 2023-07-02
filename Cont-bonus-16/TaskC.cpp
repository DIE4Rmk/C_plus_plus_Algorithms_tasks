#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

void addIterations(std::vector<int> *order, int iterator, int count_stages) {
    for (int k = iterator + 1; k < count_stages; ++k) {
        order->at(k) = 1;
    }
}

bool followStage(std::vector<int> *order, int count_tracks, int count_stages) {
    int iterator = count_stages - 1;
    while (order->at(iterator) == count_tracks) {
        --iterator;

        if (iterator < 0) {
            return false;
        }
    }

    if (order->at(iterator) >= count_tracks) {
        --iterator;
    }

    ++order->at(iterator);
    if (iterator == count_stages - 1) {
        return true;
    }

    addIterations(order, iterator, count_stages);
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int count_tracks;
    std::cin >> count_tracks;

    int count_stages;
    std::cin >> count_stages;

    int stage_number;
    std::cin >> stage_number;

    int max_n = std::max(count_tracks, count_stages);
    std::vector<int> order(max_n, 1);

    --stage_number;
    while (stage_number > 0 && followStage(&order, count_tracks, count_stages)) {
        --stage_number;
    }

    std::copy(order.begin(), order.begin() + count_stages - 1,
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << order[count_stages - 1];
    return 0;
}