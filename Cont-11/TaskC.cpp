#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

std::vector<bool> passed_nodes;
std::vector<std::string> relatives;

void sort(std::vector<int> *vector, int count, int first, int last) {
    if (first >= last) {
        return;
    }

    std::string pivot = relatives[vector->operator[]((first + last) / 2)];
    int index_i = first;
    int index_j = last;

    while (index_i <= index_j) {
        while (relatives[vector->operator[](index_i)] < pivot) {
            ++index_i;
        }
        while (relatives[vector->operator[](index_j)] > pivot) {
            --index_j;
        }

        if (index_i <= index_j) {
            std::swap(vector->operator[](index_i++), vector->operator[](index_j--));
        }
    }

    if (index_j > 0) {
        sort(vector, count, first, index_j);
    }
    if (index_i < count) {
        sort(vector, count, index_i, last);
    }
}

void dfs(int node_index, std::vector<std::vector<int>> *graph) {
    passed_nodes[node_index] = true;

    int last = static_cast<int>(graph->operator[](node_index).size() - 1);
    int count = static_cast<int>(graph->operator[](node_index).size());

    sort(&graph->operator[](node_index), count, 0, last);
    for (int vertex : graph->operator[](node_index)) {
        if (!passed_nodes[vertex]) {
            std::cout << relatives[vertex] << "\n";
            dfs(vertex, graph);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_guests;
    int count_relatives;
    std::cin >> count_guests >> count_relatives;
    std::vector<std::vector<int>> graph(count_guests);

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
    std::cout << relatives[horse_number] << "\n";

    passed_nodes = std::vector<bool>(count_guests);
    dfs(horse_number, &graph);
}
