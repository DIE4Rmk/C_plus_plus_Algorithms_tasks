#include <iostream>
#include <vector>

class BinHeap {
private:
    int size = 0;
public:
    std::vector<int> vec;

    void insrt(int item, bool flag) {
        vec.push_back(item);
        size++;
        int parent = (size - 1) / 2;
        int iter = size - 1;
        while (iter > 0 && vec[parent] < vec[iter]) {
            std::swap(vec[iter], vec[parent]);
            iter = parent;
            parent = (iter - 1) / 2;
        }
        if (flag) {
            std::cout << iter;
        }
    }

    void sort_heap(int iter) {
        int l, r, mx;
        for (;;) {
            l = 2 * iter + 1;
            r = 2 * iter + 2;
            mx = iter;
            if(l < size && vec[l] > vec[mx]) {
                mx = l;
            }

            if(r < size && vec[r] > vec[mx]) {
                mx = r;
            }
            if(mx == iter) {
                break;
            }
            std::swap(vec[iter], vec[mx]);
            iter = mx;
        }
    }

};

int main() {
    BinHeap bh;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int item;
        std::cin >> item;
        if (i == n - 1) {
            bh.insrt(item, true);
        } else {
            bh.insrt(item, false);
        }
    }
    std::cout << std::endl;
    for (auto i: bh.vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    bh.sort_heap(0);
    for (auto i: bh.vec) {
        std::cout << i << " ";
    }
    return 0;
}
