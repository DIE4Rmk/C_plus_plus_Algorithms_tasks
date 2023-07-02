#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <utility>
#include <functional>

class Graph {
    int count_vertex_;
    std::list<std::pair<int, int>> *matrix_;

public:
    explicit Graph(int count_vertex) {
        this->count_vertex_ = count_vertex;
        matrix_ = new std::list<std::pair<int, int>>[count_vertex];
    }

    ~Graph() {
        delete[] matrix_;
    }

    void addNewEdge(int u, int v, int w) {
        matrix_[u].emplace_back(v, w);
    }

    std::vector<int64_t> getShortestPathFromHead() {
        int start_vertex = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>>
                queue;
        std::vector<int64_t> distance(count_vertex_, 1e18);

        queue.push(std::make_pair(0, start_vertex));
        distance[start_vertex] = 0;

        while (!queue.empty()) {
            int u = queue.top().second;
            queue.pop();

            std::list<std::pair<int, int>>::iterator iter;
            for (iter = matrix_[u].begin(); iter != matrix_[u].end(); ++iter) {
                int vertex = (*iter).first;
                int weight = (*iter).second;

                if (distance[vertex] > distance[u] + weight) {
                    distance[vertex] = distance[u] + weight;
                    queue.push(std::make_pair(distance[vertex], vertex));
                }
            }
        }

        return distance;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_vertex;
    std::cin >> count_vertex;

    int count_arc;
    std::cin >> count_arc;

    Graph graph(count_vertex);
    for (int i = 0; i < count_arc; ++i) {
        int u;
        int v;
        int w;
        std::cin >> u >> v >> w;
        graph.addNewEdge(u, v, w);
    }

    std::vector<int64_t> distance = graph.getShortestPathFromHead();
    for (int i = 1; i < count_vertex; ++i) {
        std::cout << distance[i] << std::endl;
    }

    return 0;
}
