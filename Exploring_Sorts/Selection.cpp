
#include "Selection.h"
#include "Generation.cpp"

class Selection {
public:
    std::vector<int> toFive300;
    std::vector<int> toFive4100;
    std::vector<int> to4Thousand300;
    std::vector<int> to4Thousand4100;
    std::vector<int> halfSort300;
    std::vector<int> halfSort4100;
    std::vector<int> descending300;
    std::vector<int> descending4100;
    Selection() {
        Generation g;
        toFive300 = g.getFive(1);
        /*toFive4100 = getFive(2);
        to4Thousand300 = getThousand(1);
        to4Thousand4100 = getThousand(2);
        halfSort300 = getHalf(1);
        halfSort4100 = getHalf(2);
        descending300 = getDescending(1);
        descending4100 = getDescending(2);*/
    }

    void select_300(std::vector<int> vec) {
        for (int i = 0; i < 300; ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
        for (int size = 50; size <= 300; size += 50) {
            std::vector<int> sorted = select_all(vec, size);
        }

    }

//    std::vector<int> select_4100(std::vector<int> vec) {
//
//    }

    std::vector<int> select_all(std::vector<int> vec, int size) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < size; ++i) {
            for (int j = i; j > 0; --j) {
                std::swap(vec[j - 1], vec[j]);
            }
        }
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long milliseconds =
                std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << milliseconds << " ms" << std::endl;
        return vec;
    }

//    bool cheker(std::vector<int> vec, int size) {
//        for (int i = 1; i < size; ++i) {
//            if (vec[i - 1] > vec[i]) {
//                return false;
//            }
//        }
//        return true;
//    }
};