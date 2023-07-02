#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int left_vertex;
    int right_vertex;
    int weight;

    Edge(int left_vertex, int right_vertex, int weight) {
        this->left_vertex = left_vertex;
        this->right_vertex = right_vertex;
        this->weight = weight;
    }
};

void dfs(std::vector<std::vector<int>> *graph, std::vector<bool> *used,
         std::vector<int64_t> *distance, int vertex) {
    used->at(vertex) = true;

    for (size_t i = 0; i < graph->at(vertex).size(); ++i) {
        if (!used->at(graph->at(vertex)[i])) {
            distance->at(graph->at(vertex)[i]) = -1e18;
            dfs(graph, used, distance, graph->at(vertex)[i]);
        }
    }
}

void algorithmBellmanFord(std::vector<std::vector<int>> *graph, std::vector<Edge *> *edges,
                          std::vector<int64_t> *distance, int count_vertex, int count_arc) {
    std::vector<bool> used(count_vertex);
    used.assign(count_vertex, false);
    for (int j = 0; j < count_arc; ++j) {
        if (distance->at(edges->at(j)->left_vertex) < static_cast<int64_t>(1e18)) {
            if (distance->at(edges->at(j)->left_vertex) > -static_cast<int64_t>(1e18)) {
                if (distance->at(edges->at(j)->right_vertex) >
                    distance->at(edges->at(j)->left_vertex) + edges->at(j)->weight) {
                    distance->at(edges->at(j)->right_vertex) = -static_cast<int64_t>(1e18);
                    used.assign(count_vertex, false);
                    dfs(graph, &used, distance, edges->at(j)->right_vertex);
                }
            }
        }
    }
}

std::vector<int64_t> findDistance(std::vector<Edge *> *edges, int count_vertex, int count_arc) {
    std::vector<int64_t> distance(count_vertex, static_cast<int64_t>(1e18));

    distance[0] = 0;
    for (int i = 0; i + 1 < count_vertex; ++i) {
        for (int j = 0; j < count_arc; ++j) {
            if (distance[edges->at(j)->left_vertex] < static_cast<int64_t>(1e18)) {
                if (distance[edges->at(j)->right_vertex] >
                    distance[edges->at(j)->left_vertex] + edges->at(j)->weight) {
                    distance[edges->at(j)->right_vertex] =
                            std::max(-static_cast<int64_t>(1e18),
                                     distance[edges->at(j)->left_vertex] + edges->at(j)->weight);
                }
            }
        }
    }

    return distance;
}

void printResult(std::vector<int64_t> *distance) {
    for (size_t i = 1; i < distance->size(); ++i) {
        if (distance->at(i) > -static_cast<int64_t>(1e18)) {
            std::cout << distance->at(i) << std::endl;
            continue;
        }

        std::cout << "-inf" << std::endl;
    }
}

void inputData(std::vector<std::vector<int>> *graph, std::vector<Edge *> *edges, int count_arc) {
    for (int i = 0; i < count_arc; ++i) {
        int u;
        int v;
        int w;
        std::cin >> u >> v >> w;

        graph->at(u).push_back(v);
        edges->push_back(new Edge(u, v, w));
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_vertex;
    std::cin >> count_vertex;

    int count_arc;
    std::cin >> count_arc;

    std::vector<Edge *> edges;
    std::vector<std::vector<int>> graph(count_vertex);

    inputData(&graph, &edges, count_arc);

    std::vector<int64_t> distance = findDistance(&edges, count_vertex, count_arc);

    algorithmBellmanFord(&graph, &edges, &distance, count_vertex, count_arc);

    printResult(&distance);

    for (auto &edge : edges) {
        delete edge;
    }

    return 0;
}
