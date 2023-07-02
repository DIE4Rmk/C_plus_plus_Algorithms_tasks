//
// Created by Марк on 17.02.2023.
//

#include "Generation.h"

/*
 * Class of making reference arrays.
 */
class Generation {
    /*
     * Type 1 - from zero to five
     */
public:
    std::vector<int> getFive(int mode) {
        //Mode for 300 array
        if (mode == 1) {
            std::mt19937 rnd1(100);
            std::uniform_int_distribution<int> disFive(0, 5);
            std::vector<int> gen(301);
            for (int i = 0; i < 301; ++i) {
                gen[i] = disFive(rnd1);
                return gen;
            }
        } else {
            std::mt19937 rnd2(200);
            std::uniform_int_distribution<int> disThousand(0, 5);
            std::vector<int> gen(4101);
            for (int i = 0; i < 4101; ++i) {
                gen[i] = disThousand(rnd2);
            }
            return gen;
        }
    }

    /*
     * Type 2 - from zero to 4000
     */
    std::vector<int> getThousand(int mode) {
        //Mode for 300 array.
        if (mode == 1) {
            std::mt19937 rnd1(100);
            std::uniform_int_distribution<int> disFive(0, 4000);
            std::vector<int> gen(301);
            for (int i = 0; i < 301; ++i) {
                gen[i] = disFive(rnd1);
                return gen;
            }
        } else {
            std::mt19937 rnd2(200);
            std::uniform_int_distribution<int> disThousand(0, 4000);
            std::vector<int> gen(4101);
            for (int i = 0; i < 4101; ++i) {
                gen[i] = disThousand(rnd2);
            }
            return gen;
        }
    }

    /*
     * Type 3 - as Type 2, but makes N swaps (if a > b - swap them)
     */
    std::vector<int> getHalf(int mode) {
        if (mode == 1) {
            std::vector<int> gen = getThousand(1);
            for (int i = 0; i < 290; i += 10) {
                if (gen[i] > gen[i + 1]) {
                    std::swap(gen[i], gen[i + 1]);
                }
            }
            return gen;
        } else {
            std::vector<int> gen = getThousand(2);
            for (int i = 0; i < 4000; i += 100) {
                if (gen[i] > gen[i + 1]) {
                    std::swap(gen[i], gen[i + 1]);
                }
            }
            return gen;
        }
    }
    /*
     * Type 4 - Nums form 4100 to 1.
     */
    std::vector<int> getDescending() {
        std::vector<int> gen(4101);
        for (int i = 4100; i >= 1 ; --i) {
            gen[i] = i;
        }
        return gen;
    }

};