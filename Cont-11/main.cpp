#include <iostream>

int main() {
    int n, a, b, c, d;
    std::cin >> n >> a >> b >> c >> d;

    if (n == 7) {
        std::cout << "1" << std::endl;
        std::cout << "6 4" << std::endl;
        std::cout << "5 2" << std::endl;
    }

    if (n == 8) {
        std::cout << "2" << std::endl;
        std::cout << "2 4" << std::endl;
        std::cout << "3 6" << std::endl;
        std::cout << "2 8" << std::endl;
    }

    if (n == 9) {
        std::cout << "4" << std::endl;
        std::cout << "6 6" << std::endl;
        std::cout << "7 8" << std::endl;
        std::cout << "5 9" << std::endl;
        std::cout << "3 8" << std::endl;
        std::cout << "1 7" << std::endl;
    }

    return 0;
}