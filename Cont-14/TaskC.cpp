#include <iostream>
#include <vector>
#include <algorithm>

void printResult(std::vector<std::vector<int64_t>> *graph, int count_vertex) {
    for (int iter_i = 0; iter_i < count_vertex; ++iter_i) {
        for (int iter_j = 0; iter_j < count_vertex; ++iter_j) {
            if (iter_j != iter_i) {
                std::cout << iter_i << " " << iter_j << " ";

                if (graph->operator[](iter_i)[iter_j] != static_cast<int64_t>(1e18)) {
                    std::cout << graph->operator[](iter_i)[iter_j] << std::endl;
                } else {
                    std::cout << -1 << std::endl;
                }
            }
        }
    }
}

void floydWarshell(std::vector<std::vector<int64_t>> *graph, int count_vertex) {
    for (int iter_i = 0; iter_i < count_vertex; ++iter_i) {
        for (int iter_j = 0; iter_j < count_vertex; ++iter_j) {
            for (int iter_k = 0; iter_k < count_vertex; ++iter_k) {
                graph->operator[](iter_j)[iter_k] =
                        std::min(graph->operator[](iter_j)[iter_k],
                                 graph->operator[](iter_j)[iter_i] + graph->operator[](iter_i)[iter_k]);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_vertex;
    std::cin >> count_vertex;

    int count_arc;
    std::cin >> count_arc;
    std::vector<std::vector<int64_t>> graph(count_vertex, std::vector<int64_t>(count_vertex, 1e18));

    for (int i = 0; i < count_arc; ++i) {
        int u;
        int v;
        int w;
        std::cin >> u >> v >> w;
        graph[u][v] = w;
    }

    floydWarshell(&graph, count_vertex);

    printResult(&graph, count_vertex);

    return 0;
}
