#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <set>

/*
 * Рахильский Марк Даниилович, БПИ-218.
 * КДЗ-2
 * Реализованы алгоритм наивного поиска и КМП на обычных гранях. Третий алгоритм написан, но в
 * тестах не используется.
 *
 * Порядок тестов бинарки и ДНК без вставок, после тоже самое со вставками.
 */

void pushVarsStrings(std::string &str, std::set<char> &chars, std::vector<std::string> &allStrings);

std::vector<std::vector<int64_t>> testTime(std::string &s, int insert = 0);

////////////////////
///Блок Алгосов.
/// Все вариации строки по символам подстановки, отсеивание невозможных символов.
/// \param find
/// \param text
/// \return
std::vector<std::string> getAllStrings(std::string &str, std::string &text) {
    std::vector<std::string> vecStrs; //result.
    std::set<char> chars; //container of all chars in text.
    for (auto item: text) { // All possible chars are already in &text
        chars.insert(item);
    }
    pushVarsStrings(str, chars, vecStrs);
    return vecStrs;
}

void pushVarsStrings(std::string &str, std::set<char> &chars, std::vector<std::string> &allStrings) {
    bool flag = false;
    size_t sz = str.size();
    for (size_t i = 0; i < sz; i++) {
        if (str[i] == '?') {
            for (auto ch: chars) {
                std::string str2 = str;
                str2[i] = ch;
                flag = true;
                pushVarsStrings(str2, chars, allStrings);
            }
        }
    }
    if (!flag) {
        allStrings.push_back(str);
    }
}

/// Алгоритм обычного КМП
/// \param pattern
/// \return
std::vector<int> compute_prefix_function(std::string pattern) {
    int m = int(pattern.size());
    std::vector<int> prefix(m);
    prefix[0] = 0;
    int k = 0;
    for (int i = 1; i < m; ++i) {
        while (k > 0 && pattern[i] != pattern[k]) {
            k = prefix[k - 1];
        }
        if (pattern[i] == pattern[k]) {
            ++k;
        }
        prefix[i] = k;
    }
    return prefix;
}

void kmp(std::string &pattern, std::string &text) {
    size_t n = text.size();
    size_t m = pattern.size();
    auto allStrings = getAllStrings(pattern, text);
    for (auto &patI: allStrings) {
        std::vector<int> prefix = compute_prefix_function(patI);
        int q = 0;
        for (auto i = 0; i < n; ++i) {
            while (q > 0 && text[i] != patI[q]) {
                q = prefix[q - 1];
            }
            if (text[i] == patI[q]) {
                ++q;
            }
            if (q == m) { //m - pattern size.
                continue;
                //q = prefix[q - 1];
            }
        }
    }
}

/// КМП с утонченными гранями, НЕ ИСПОЬЗУЕТСЯ
/// \param pat
/// \param lps
void compute_lps(std::string pat, std::vector<int> &lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pat.size()) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/// НЕ ИСПОЛЬЗУЕТСЯ
/// \param pat
/// \param txt
void kmpFacets(std::string pat, std::string txt) {
    std::vector<int> lps(pat.size());
    compute_lps(pat, lps);

    int i = 0, j = 0;
    while (i < txt.size()) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
        } else {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }

        if (j == pat.size()) {
            std::cout << "Pattern found at index " << i - j << std::endl;
            j = lps[j - 1];
        }
    }
}

/// Наивный алгоритм
/// \param pattern
/// \param text
void algo1_commonSearch(std::string &pattern, std::string &text) {
    size_t n = text.size();
    size_t m = pattern.size();
    for (auto i = 0; i < n; i++) {
        bool found = false;
        for (auto j = 0; j < m; j++) {
            if (text[i + j] != pattern[j] && pattern[j] != '?') {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Pattern found at index " << i << std::endl;
        }
    }
}


/////////////////
////Блок шаблонов.
/// Генерация шаблона из 2-х символов.
/// \param count - Insertions
/// \return
std::string getBin(int count) {
    std::string str(count, ' ');
    srand(time(nullptr));

    for (int i = 0; i < count; i++) {
        int rnd = rand() % 2;
        switch (rnd) {
            case 0:
                str[i] = 'a';
                break;
            case 1:
                str[i] = 'b';
                break;
            default:
                break;
        }
    }
    return str;
}

/// Генерация шаблона из 4-х символов.
/// \param count - Insertions
/// \return
std::string getDNA(int count) {
    std::string str(count, ' ');
    srand(time(nullptr));

    for (int i = 0; i < count; i++) {
        int r = rand() % 4;
        switch (r) {
            case 0:
                str[i] = 'a';
                break;
            case 1:
                str[i] = 'b';
                break;
            case 2:
                str[i] = 'c';
                break;
            case 3:
                str[i] = 'd';
                break;
            default:
                str[i] = ' ';
                break;
        }
    }
    return str;
}

/// Вставка знака "?" рандомно.
/// \param text - шаблон
/// \param num - кол-во знаков для вставки.
void putQuestion(std::string &text, int num) {
    srand(time(nullptr));
    for (size_t i = 0; i < num; i++) {
        auto rnd = rand() % (text.size() - 1);
        text[rnd] = '?';
    }
}

/// Расчет времени для прохода алгоритмов по шабонам.
/// \param str - сгенерированная строка
/// \param numInserts - кол-во вставок
/// \return
std::vector<std::vector<int64_t>> testTime(std::string &str, int numInserts) {
    int step = 100;
    srand(time(nullptr));
    int pos = rand() % 3000;
    std::vector<std::vector<int64_t>> test_table(30, std::vector<int64_t>(3, 0));
    int i = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    for (auto j = 0; j < 10; ++j) {
        while (step <= 3000) {
            auto sub_str = str.substr(pos, step);
            //There isn't any "?".
            if (numInserts > 0) {
                putQuestion(sub_str, numInserts);
            }
            //Algo 1
            start = std::chrono::high_resolution_clock::now();
            algo1_commonSearch(sub_str, str);
            elapsed = std::chrono::high_resolution_clock::now() - start;
            test_table[i][0] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
            // Algo 2
            start = std::chrono::high_resolution_clock::now();
            kmp(sub_str, str);
            elapsed = std::chrono::high_resolution_clock::now() - start;
            test_table[i][1] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
            test_table[i][2] = sub_str.size();
            step += 100;
            ++i;
        }
    }
    for (auto &time: test_table) {
        for (int64_t &x: time) {
            x /= 10;
        }
    }
    return test_table;
}

//Без символов подстановки, 10000 символов, бинарный алфавит.
std::vector<std::vector<int64_t>> time_binAlph_1e4() {
    std::string str = getBin(1e4);
    return testTime(str);
}

//Без символов подстановки, 100000 символов, бинарный алфавит.
std::vector<std::vector<int64_t>> time_binAlph_1e5() {
    std::string str = getBin(1e5);
    return testTime(str);
}

//Без символов подстановки, 10000 символов, 4-символьный алфавит.
std::vector<std::vector<int64_t>> time_dna_1e4() {
    std::string str = getDNA(1e4);
    return testTime(str);
}

//Без символов подстановки, 100000 символов, 4-символьный алфавит.
std::vector<std::vector<int64_t>> time_dna_1e5() {
    std::string str = getDNA(1e5);
    return testTime(str);
}

//С X символов подстановки, 10000 символов, бинарный алфавит.
std::vector<std::vector<int64_t>> time_binAlphs_withInserts_1e4(int num) {
    std::string str = getBin(10000);
    return testTime(str, num);
}

//С X символов подстановки, 100000 символов, бинарный алфавит.
std::vector<std::vector<int64_t>> time_binAlphs_withInserts_1e5(int num) {
    std::string str = getBin(100000);
    return testTime(str, num);

}

//С X символов подстановки, 10000 символов, 4-символьный алфавит.
std::vector<std::vector<int64_t>> time_dna_withInserts_1e4(int num) {
    std::string str = getDNA(10000);
    return testTime(str, num);
}

//С X символов подстановки, 100000 символов, 4-символьный алфавит.
std::vector<std::vector<int64_t>> time_dna_withInserts_1e5(int num) {
    std::string str = getDNA(100000);
    return testTime(str, num);
}
/// Прокидка в CSV
/// \param path - сгенерированый файл
/// \param time - таблица тестов
void pushToTable(const std::string &path, const std::vector<std::vector<int64_t>> &time) {
    std::ofstream of;
    of.open(path);
    for (auto item: time) {
        for (auto j = 0; j < 3; j++) {
            if (j < 2) {
                of << item[j] << ";";
            } else {
                of << item[j] << ";" << "\n";
            }
        }
    }
    of.close();
}

int main() {
    pushToTable("time_binAlph_1e4.csv", time_binAlph_1e4());
    pushToTable("time_binAlph_1e5.csv", time_binAlph_1e5());
    pushToTable("time_dna_1e4.csv", time_dna_1e4());
    pushToTable("time_dna_1e5.csv", time_dna_1e5());
    // With Inserts
    for (auto i = 1; i < 5; i++) {
        pushToTable("binAlphs_withInserts_1e4_" + std::to_string(i) +
                    "isnerted.csv", time_binAlphs_withInserts_1e4(i));
        pushToTable("binAlphs_withInserts_1e5_" + std::to_string(i) +
                    "isnerted.csv", time_binAlphs_withInserts_1e5(i));
        pushToTable("DNA_WithInserts_1e4_" + std::to_string(i) +
                    "isnerted.csv", time_dna_withInserts_1e4(i));
        pushToTable("DNA_WithInserts_1e5_" + std::to_string(i) +
                    "isnerted.csv", time_dna_withInserts_1e5(i));
    }
}