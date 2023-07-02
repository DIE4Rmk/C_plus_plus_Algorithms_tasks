#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>

struct Tree {
    char ch;
    int rate;
    Tree *left;
    Tree *right;
};

struct Equals {
    bool operator()(const Tree *first_tree, const Tree *second_tree) const {
        return first_tree->rate > second_tree->rate;
    }
};

Tree *createTree(char ch, int rate, Tree *left, Tree *right) {
    Tree *tree = new Tree();
    tree->ch = ch;
    tree->rate = rate;
    tree->left = left;
    tree->right = right;

    return tree;
}

void cleanTree(Tree *root) {
    if (!root) {
        return;
    }

    cleanTree(root->right);
    cleanTree(root->left);
    delete root;
}

void encryp(Tree *root, const std::string &input, std::map<char, std::string> *huff_encryp) {
    if (!root) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        if (input.empty()) {
            huff_encryp->operator[](root->ch) = "0";
        } else {
            huff_encryp->operator[](root->ch) = input;
        }
    }

    encryp(root->left, input + "0", huff_encryp);
    encryp(root->right, input + "1", huff_encryp);
}

std::map<char, std::string> createHuffman(const std::string &input) {
    std::map<char, int> rate;
    for (char ch : input) {
        ++rate[ch];
    }

    std::priority_queue<Tree *, std::vector<Tree *>, Equals> queue;
    for (auto pair : rate) {
        Tree *nw_branch = createTree(pair.first, pair.second, nullptr, nullptr);
        queue.push(nw_branch);
    }

    while (queue.size() > 1) {
        Tree *left = queue.top();
        queue.pop();

        Tree *right = queue.top();
        queue.pop();

        int rates = left->rate + right->rate;
        Tree *nw_branch = createTree('0', rates, left, right);
        queue.push(nw_branch);
    }

    Tree *root = queue.top();
    std::map<char, std::string> huff_encryp;
    encryp(root, "", &huff_encryp);
    cleanTree(root);

    return huff_encryp;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string input;
    std::cin >> input;
    std::map<char, std::string> huff_encryp = createHuffman(input);

    std::string ans_huff;
    for (auto &item : input) {
        ans_huff += huff_encryp[item];
    }

    std::cout << huff_encryp.size() << " " << ans_huff.size() << "\n";
    for (const auto &pair : huff_encryp) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    std::cout << ans_huff << "\n";

    return 0;
}
