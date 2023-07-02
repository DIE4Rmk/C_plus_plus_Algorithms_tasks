#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "BigIntegerUtils2.h"

int findChoice(int count_days, BigInteger k_number) {
    std::vector<int> select;
    select.assign(count_days, 0);

    int iterator = 0;
    int position = count_days - 1;
    while (iterator < count_days) {
        select[position] = (k_number % (count_days - iterator) + 1).toInt();
        --position;

        k_number = k_number / (count_days - iterator);
        ++iterator;
    }

    std::copy(select.begin(), select.end() - 1, std::ostream_iterator<int>(std::cout, " "));

    return select[select.size() - 1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int count_days;
    std::cin >> count_days;

    std::string k_number_string;
    std::cin >> k_number_string;
    BigInteger k_number = stringToBigInteger(k_number_string);

    std::cout << findChoice(count_days, k_number - 1);
    return 0;
}