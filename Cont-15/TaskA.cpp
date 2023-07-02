#include <iostream>
#include <vector>
#include <algorithm>

int deq[5001];
int qeq[5001];
int ptr[5001];

struct Node {
    int first;
    int second;
    int capacity;
    int stream;

    Node(int first, int second, int capacity, int stream) {
        this->first = first;
        this->second = second;
        this->capacity = capacity;
        this->stream = stream;
    }
};

void push(std::vector<int> *graph, std::vector<Node> *nodes, int first, int second, int length) {
    Node e1(first, second, length, 0);
    Node e2(second, first, 0, 0);

    graph[first].push_back(static_cast<int>(nodes->size()));
    nodes->push_back(e1);

    graph[second].push_back(static_cast<int>(nodes->size()));
    nodes->push_back(e2);
}

int it;
int s = 0;

bool bfs(std::vector<int> *graph, std::vector<Node> *nodes, int count) {
    int it_2 = 0;
    qeq[it_2] = s;
    ++it_2;

    for (int i = 0; i < count; ++i) {
        deq[i] = -1;
    }
    deq[s] = 0;

    int it_1 = 0;
    while (it_1 < it_2 && deq[it] == -1) {
        int v = qeq[it_1];

        for (size_t i = 0; i < graph[v].size(); ++i) {
            int id = graph[v][i], to = nodes->operator[](id).second;

            if (deq[to] == -1 && nodes->operator[](id).stream < nodes->operator[](id).capacity) {
                qeq[it_2++] = to;
                deq[to] = deq[v] + 1;
            }
        }

        ++it_1;
    }

    return deq[it] != -1;
}

int dfs(std::vector<int> *graph, std::vector<Node> *nodes, int vertex, int stream) {
    if (!stream) {
        return 0;
    }

    if (vertex == it) {
        return stream;
    }

    for (; ptr[vertex] < static_cast<int>(graph[vertex].size()); ++ptr[vertex]) {
        int i = graph[vertex][ptr[vertex]];
        int to = nodes->operator[](i).second;

        if (deq[to] != deq[vertex] + 1) {
            continue;
        }

        int pushed =
                dfs(graph, nodes, to,
                    std::min(stream, nodes->operator[](i).capacity - nodes->operator[](i).stream));

        if (pushed != 0) {
            nodes->operator[](i).stream += pushed;
            nodes->operator[](i ^ 1).stream -= pushed;
            return pushed;
        }
    }

    return 0;
}

void maxStream(std::vector<int> *graph, std::vector<Node> *nodes, int count) {
    int stream = 0;

    while (bfs(graph, nodes, count)) {
        for (size_t i = 0; i < count; ++i) {
            ptr[i] = 0;
        }

        while (int pushed = dfs(graph, nodes, s, 1e9)) {
            stream += pushed;
        }
    }

    std::cout << stream;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> g[5001];

    int count_vertex;
    int count_edge;

    std::cin >> count_edge >> count_vertex;
    it = count_edge - 1;

    std::vector<Node> nodes;
    for (size_t i = 0; i < count_vertex; ++i) {
        int u;
        int v;
        int length;
        std::cin >> u >> v >> length;
        push(g, &nodes, u - 1, v - 1, length);
    }

    maxStream(g, &nodes, count_edge);
    return 0;
}
