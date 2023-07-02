#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

struct City {
    int x, y;
};

double calculateDistance(const City& city1, const City& city2) {
    double x_diff = city1.x - city2.x;
    double y_diff = city1.y - city2.y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

double calculateTotalDistance(const std::vector<int>& route, const std::vector<City>& cities) {
    double totalDistance = 0.0;
    for (size_t i = 0; i < route.size() - 1; ++i) {
        int cityIndex1 = route[i];
        int cityIndex2 = route[i + 1];
        totalDistance += calculateDistance(cities[cityIndex1], cities[cityIndex2]);
    }
    return totalDistance;
}

void generatePermutations(std::vector<std::vector<int>>& permutations, std::vector<int>& route, int start) {
    if (start == route.size() - 1) {
        permutations.push_back(route);
        return;
    }

    for (size_t i = start; i < route.size(); ++i) {
        std::swap(route[start], route[i]);
        generatePermutations(permutations, route, start + 1);
        std::swap(route[start], route[i]);
    }
}

std::vector<int> findShortestRoute(const std::vector<City>& cities) {
    const int numCities = cities.size();

    std::vector<int> route(numCities);
    for (int i = 0; i < numCities; ++i) {
        route[i] = i;
    }

    std::vector<std::vector<int>> permutations;
    generatePermutations(permutations, route, 1); // Start from index 1 to exclude the first city

    double shortestDistance = std::numeric_limits<double>::max();
    std::vector<int> shortestRoute;

    for (const auto& permutation : permutations) {
        double distance = calculateTotalDistance(permutation, cities);
        if (distance < shortestDistance) {
            shortestDistance = distance;
            shortestRoute = permutation;
        }
    }

    return shortestRoute;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<City> cities(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> cities[i].x >> cities[i].y;
    }

    std::vector<int> shortestRoute = findShortestRoute(cities);

    for (auto it = shortestRoute.rbegin(); it != shortestRoute.rend(); ++it) {
        std::cout << *it + 1  << " ";
    }
    std::cout << "\n";

    return 0;
}
