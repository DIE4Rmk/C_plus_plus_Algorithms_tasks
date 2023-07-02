#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <unordered_map>
#include <algorithm>

int findSumOfDigit(int number) {
    int sum = 0;
    while (number != 0) {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}

std::vector<int> createDelta(int point) {
    std::vector<int> delta_vector;
    delta_vector.push_back(point % 10);

    if (point / 10 > 0) {
        delta_vector.push_back(point / 10);
        delta_vector.push_back(point % 100);
    }
    if (point / 100 > 0) {
        delta_vector.push_back(point / 10 % 10);
        delta_vector.push_back(point / 100);
        delta_vector.push_back(point % 1000);
    }
    if (point / 1000 > 0) {
        delta_vector.push_back(point / 100 % 10);
        delta_vector.push_back(point / 10 % 100);
        delta_vector.push_back(point / 1000);
        delta_vector.push_back(point % 10000);
    }

    return delta_vector;
}

std::vector<std::pair<int, int>> getHeir(int point, int max_num) {
    std::vector<int> delta_vector = createDelta(point);

    std::vector<std::pair<int, int>> heir;
    for (int delta : delta_vector) {
        int digits_sum = findSumOfDigit(delta);
        if (point + delta <= max_num && point + delta != point) {
            heir.emplace_back(point + delta, digits_sum);
        }
        if (point - delta > 0 && point + delta != point) {
            heir.emplace_back(point - delta, digits_sum);
        }
    }

    return heir;
}

std::unordered_map<uint64_t, int> createDistanceMap(int a, int b) {
    std::unordered_map<uint64_t, int> distance;
    distance[a] = 0;
    distance[b] = 1e9 * 2;

    return distance;
}

void printResultOfFind(std::unordered_map<int, int> *ancestors, int a, int b) {
    std::vector<int> route;
    while (b != a) {
        route.push_back(b);
        b = ancestors->operator[](b);
    }
    route.push_back(a);

    std::reverse(route.begin(), route.end());
    std::cout << route.size() - 1 << std::endl;
    for (size_t i = 1; i < route.size(); ++i) {
        int action = route[i] - route[i - 1];
        if (action > 0) {
            std::cout << "+";
        }

        std::cout << action << std::endl;
    }
}

void findNumber(int a, int b, int max_num) {
    std::unordered_map<uint64_t, int> distance = createDistanceMap(a, b);

    std::set<std::pair<int, int>> evaluations;
    evaluations.insert(std::make_pair(distance[a], a));

    bool route_find = false;
    std::unordered_map<int, int> ancestors;
    while (!evaluations.empty()) {
        std::pair<int, int> pair = *evaluations.begin();
        int w = pair.first;
        int v = pair.second;

        evaluations.erase(evaluations.begin());
        distance[v] = w;
        if (v == b) {
            route_find = true;
            break;
        } else {
            std::vector<std::pair<int, int>> heirs = getHeir(v, max_num);
            for (auto heir : heirs) {
                if (distance.find(heir.first) == distance.end() ||
                    distance[heir.first] > (distance[v] + heir.second)) {
                    evaluations.erase(std::make_pair(distance[heir.first], heir.first));
                    ancestors[heir.first] = v;
                    distance[heir.first] = distance[v] + heir.second;
                    evaluations.insert(std::make_pair(distance[heir.first], heir.first));
                }
            }
        }
    }

    if (route_find) {
        std::cout << distance[b] << std::endl;
        printResultOfFind(&ancestors, a, b);
        return;
    }
    std::cout << -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int max_num;
    std::cin >> max_num;

    int a;
    int b;
    std::cin >> a >> b;

    findNumber(a, b, max_num);
    return 0;
}
