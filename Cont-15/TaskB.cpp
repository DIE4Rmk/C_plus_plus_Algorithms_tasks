#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <algorithm>

int const kMax = 1e9;

struct Edge {
    int cap = 0;
    int flow = 0;
};

class Graph {
private:
    std::vector<std::vector<Edge>> graph_;

    int count_vertex_;
    int start_ = 0;
    int end_ = 0;
    bool correct_ = true;

    std::vector<int> distance_;
    std::vector<int> remain_;

    bool bfs() {
        std::queue<int> queue;

        distance_.assign(graph_.size(), kMax);
        distance_[start_] = 0;

        queue.push(start_);
        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            for (int i = 0; i < static_cast<int>(graph_.size()); ++i) {
                if (graph_[current][i].flow < graph_[current][i].cap && distance_[i] == kMax) {
                    distance_[i] = distance_[current] + 1;
                    queue.push(i);
                }
            }
        }

        return distance_[end_] != kMax;
    }

    int dfs(int current, int capture) {
        if (current == end_ || capture == 0) {
            return capture;
        }

        for (int top = remain_[current]; top < static_cast<int>(graph_.size()); ++top) {
            if (distance_[top] == distance_[current] + 1) {
                int diff = dfs(
                        top, std::min(graph_[current][top].cap - graph_[current][top].flow, capture));
                if (diff != 0) {
                    graph_[current][top].flow += diff;
                    graph_[top][current].flow -= diff;
                    return diff;
                }
            }
        }
        return 0;
    }

public:
    explicit Graph(int count_vertex) {
        this->count_vertex_ = count_vertex;
        distance_.assign(count_vertex, 0);
        remain_.assign(count_vertex, 0);
    }

    [[nodiscard]] bool getCorrect() const {
        return correct_;
    }

    int current_stream = 0;

    int findMaxStream() {
        while (bfs()) {
            remain_.assign(graph_.size(), 0);
            int stream = dfs(start_, kMax);

            while (stream != 0) {
                current_stream += stream;
                stream = dfs(start_, kMax);
            }
        }

        return current_stream;
    }

    static std::map<std::pair<int, int>, int> initTable(
            std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> const &table) {
        std::map<std::pair<int, int>, int> pairs;

        int counter = 0;
        for (auto &it : table) {
            pairs[it.first] = counter;
            ++counter;
        }

        return pairs;
    }

    void fillDesk(std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> *table,
                  std::map<std::pair<int, int>, int> *pairs) {
        std::pair<int, int> start_pair;
        std::cin >> start_pair.first;
        std::cin >> start_pair.second;

        std::pair<int, int> end_pair;
        std::cin >> end_pair.first;
        std::cin >> end_pair.second;

        table->operator[](start_pair).push_back(end_pair);
        table->operator[](end_pair).push_back(start_pair);

        if (pairs->find(start_pair) != pairs->end() && pairs->find(end_pair) != pairs->end()) {
            start_ = 2 * pairs->operator[](start_pair) + 1;
            end_ = 2 * pairs->operator[](end_pair);
            graph_[start_ - 1][start_].cap = kMax;
            graph_[end_][end_ + 1].cap = kMax;
            return;
        }

        correct_ = false;
    }

    void inputPairs(std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> *table) const {
        for (int i = 0; i < count_vertex_; ++i) {
            std::pair<int, int> start_pair;
            std::cin >> start_pair.first;
            std::cin >> start_pair.second;

            std::pair<int, int> end_pair;
            std::cin >> end_pair.first;
            std::cin >> end_pair.second;
            table->operator[](start_pair).push_back(end_pair);
            table->operator[](end_pair).push_back(start_pair);
        }
    }

    void inputAllData() {
        std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> table;
        inputPairs(&table);

        graph_.resize(table.size() * 2);
        for (auto &x : graph_) {
            x.resize(2 * table.size());
        }

        std::map<std::pair<int, int>, int> pairs = initTable(table);

        int iter = 0;
        for (auto &iter_i : table) {
            graph_[iter * 2][iter * 2 + 1].cap = 1;
            for (auto &iter_j : iter_i.second) {
                graph_[iter * 2 + 1][pairs[iter_j] * 2].cap = 1;
            }
            ++iter;
        }

        fillDesk(&table, &pairs);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_vertex;
    std::cin >> count_vertex;

    Graph graph(count_vertex);
    graph.inputAllData();

    if (graph.getCorrect()) {
        std::cout << graph.findMaxStream();
        return 0;
    }

    std::cout << 0;
    return 0;
}