#include <iostream>
#include <vector>
#include <algorithm>

struct Tree {
    int f;
    int s;
    int len;
};

std::vector<int> par;
std::vector<int> depth;

bool iterator(Tree x, Tree y) {
    return x.len < y.len;
}

int ch(int n) {
    if (par[n] == n) {
        return n;
    }
    return par[n] = ch(par[n]);
}

int gtch(int x, int y) {
    x = ch(x);
    y = ch(y);
    if (x == y) {
        return 0;
    }
    if (depth[x] < depth[y]) {
        std::swap(x, y);
    }
    par[y] = x;
    if (depth[x] == depth[y]) {
        depth[x]++;
    }
    return 1;
}

int main() {
    std::vector<Tree> vec;
    int n, m;
    std::cin >> n >> m;
    par.resize(n + 1);
    depth.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        par[i] = i;
        depth[i] = 0;
    }
    vec.resize(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> vec[i].f >> vec[i].s >> vec[i].len;
    }
    std::sort(vec.begin(), vec.end(), iterator);
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        if (gtch(vec[i].f, vec[i].s)) {
            ans += vec[i].len;
        }
    }
    std::cout << ans;
    return 0;
}
