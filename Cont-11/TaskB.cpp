#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

std::vector<bool> passed_nodes;
std::vector<int> graph_interval;

void bfs(int horse_number, std::vector<std::vector<int>>* graph) {
    std::queue<int> queue_nodes;
    queue_nodes.push(horse_number);
    passed_nodes[horse_number] = true;

    while (!queue_nodes.empty()) {
        int current = queue_nodes.front();
        queue_nodes.pop();

        for (int vertex : graph->operator[](current)) {
            if (!passed_nodes[vertex]) {
                graph_interval[vertex] = graph_interval[current] + 1;
                queue_nodes.push(vertex);
                passed_nodes[vertex] = true;
            }
        }
    }
}

void printGuests(int count_guests, std::vector<std::string>* relatives) {
    int count_links = -1e9;

    for (int i : graph_interval) {
        if (i > count_links) {
            count_links = i;
        }
    }

    std::vector<std::string> vec_links;
    for (int i_index = 0; i_index <= count_links; ++i_index) {
        for (int j = 0; j < count_guests; ++j) {
            if (graph_interval[j] == i_index) {
                vec_links.push_back(relatives->operator[](j));
            }
        }

        std::sort(vec_links.begin(), vec_links.end());
        for (int j_index = 0; j_index < vec_links.size(); ++j_index) {
            std::cout << vec_links[j_index] << "\n";
        }

        vec_links.clear();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_guests;
    int count_relatives;
    std::cin >> count_guests >> count_relatives;
    std::vector<std::vector<int>> graph(count_guests);

    std::vector<std::string> relatives;
    for (int i = 0; i < count_guests; ++i) {
        int number;
        std::cin >> number;

        std::string name;
        std::getline(std::cin, name);
        name = name.substr(1, name.length() - 1);
        relatives.push_back(name);
    }

    for (int i = 0; i < count_relatives; ++i) {
        int left_link;
        int right_link;
        std::cin >> left_link >> right_link;
        graph[left_link].push_back(right_link);
        graph[right_link].push_back(left_link);
    }

    int horse_number;
    std::cin >> horse_number;

    passed_nodes = std::vector<bool>(count_guests);
    graph_interval = std::vector<int>(count_guests);

    bfs(horse_number, &graph);
    printGuests(count_guests, &relatives);

    return 0;
}
