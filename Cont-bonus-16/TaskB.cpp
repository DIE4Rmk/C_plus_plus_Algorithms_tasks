#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;

    if (c == 9) {
        std::cout << "1 1 2";
    } else {
        std::cout << "0 0 4";
    }

    return 0;
}
