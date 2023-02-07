/*
  Палиндром - это строка, которая читается одинаково как справа налево, так и слева направо.
  На вход программы поступает набор больших латинских букв
 (не обязательно различных). Разрешается переставлять буквы, а также удалять некоторые буквы.
 Требуется из данных букв по указанным правилам составить палиндром наибольшей длины, а если
 таких палиндромов несколько, то выбрать первый из них в алфавитном порядке.
 */

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    const int ascii = 65;
    int n;
    std::cin >> n;
    std::string str;
    std::vector<int> vec(26, 0);
    std::cin >> str;
    for (int i = 0; i < str.size(); ++i) {
        vec[static_cast<int>(str[i] - ascii)]++;
    }
    std::string ans;
    bool flag = false;
    char mid;
    int iter = 0;
    for (int i = 0; i < 26; ++i) {
        if (vec[i] % 2 == 1 && !flag) {
            flag = true;
            mid = static_cast<char>(i + ascii);
        }
        if (vec[i] != 0) {
            ans.insert(iter, vec[i] / 2, static_cast<char>(i + ascii));
            iter += vec[i] / 2;
        }
    }
    if (flag) {
        ans = ans + mid + std::string(ans.rbegin(), ans.rend());
    } else {
        ans = ans + std::string(ans.rbegin(), ans.rend());
    }
    std::cout << ans;
}