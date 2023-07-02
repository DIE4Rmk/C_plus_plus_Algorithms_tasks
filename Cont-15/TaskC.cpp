#include <iostream>
#include <vector>
#include <algorithm>

int findValence(char name) {
    if (name == 'H') {
        return 1;
    } else if (name == 'O') {
        return 2;
    } else if (name == 'N') {
        return 3;
    } else if (name == 'C') {
        return 4;
    } else {
        return 0;
    }
}

class Edge {
public:
    int first;
    int second;
    int stream;

    Edge(int first, int second, int stream) {
        this->first = first;
        this->second = second;
        this->stream = stream;
    }
};

int64_t sum = 0;
int64_t find_sum = 0;

class Graph {
private:
    int length_;
    int count_vertex_;

public:
    std::vector<bool> checked_vertex;
    std::vector<std::vector<Edge>> edges;

    Graph(int height, int width) {
        this->length_ = width;
        this->count_vertex_ = height * width + 2;
        checked_vertex.resize(count_vertex_, false);
        edges.resize(count_vertex_);
    }

    [[nodiscard]] int getCountVertex() const {
        return count_vertex_;
    }

    void pushNewEdge(int first, int second, int stream = 1) {
        edges[first].push_back(Edge(first, second, stream));
    }

    void uploadCapacity(int n, int m) {
        for (int index_i = 0; index_i < n; ++index_i) {
            for (int index_j = 0; index_j < m; ++index_j) {
                char name;
                std::cin >> name;

                int count = index_j % 2 + index_i % 2;
                if (count % 2 == 0) {
                    pushNewEdge(0, findNumber(index_i, index_j), findValence(name));
                    find_sum += findValence(name);

                    if (index_i < n - 1) {
                        pushNewEdge(findNumber(index_i, index_j), findNumber(index_i + 1, index_j));
                    }
                    if (index_j < m - 1) {
                        pushNewEdge(findNumber(index_i, index_j), findNumber(index_i, index_j + 1));
                    }
                    if (index_i >= 1) {
                        pushNewEdge(findNumber(index_i, index_j), findNumber(index_i - 1, index_j));
                    }
                    if (index_j >= 1) {
                        pushNewEdge(findNumber(index_i, index_j), findNumber(index_i, index_j - 1));
                    }
                } else {
                    pushNewEdge(findNumber(index_i, index_j), count_vertex_ - 1, findValence(name));
                    sum += findValence(name);
                }
            }
        }
    }

    void initialize() {
        for (int i = 0; i < count_vertex_; ++i) {
            checked_vertex[i] = false;
        }
    }

    [[nodiscard]] int findNumber(int index_i, int index_j) const {
        return index_i * length_ + index_j + 1;
    }
};

int findBackEdge(Graph *graph, Edge current_edge) {
    for (int child = 0; child < graph->edges[current_edge.second].size(); ++child) {
        if (graph->edges[current_edge.second][child].second == current_edge.first) {
            return child;
        }
    }

    return -1;
}

int64_t stream_value = 0;

int addStream(Graph *graph, int value, int capacity) {
    graph->checked_vertex[value] = true;

    if (value == graph->getCountVertex() - 1) {
        stream_value += capacity;
        return capacity;
    }

    for (size_t iter = 0; iter < graph->edges[value].size(); ++iter) {
        Edge edge = graph->edges[value][iter];

        if (graph->checked_vertex[edge.second] || edge.stream == 0) {
            continue;
        }

        int current_capacity = addStream(graph, edge.second, std::min(edge.stream, capacity));

        if (current_capacity > 0) {
            graph->edges[value][iter].stream -= current_capacity;
            int number = findBackEdge(graph, edge);

            if (number != -1) {
                graph->edges[edge.second][number].stream += current_capacity;
            } else {
                graph->edges[edge.second].push_back(Edge(edge.second, value, current_capacity));
            }

            return current_capacity;
        }
    }

    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int m;
    std::cin >> m;

    Graph graph = Graph(n, m);
    graph.uploadCapacity(n, m);

    while (addStream(&graph, 0, 5)) {
        graph.initialize();
    }

    if (stream_value != find_sum || stream_value != sum || stream_value == 0) {
        std::cout << "Invalid";
    } else {
        std::cout << "Valid";
    }

    return 0;
}
