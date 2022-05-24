#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

using std::vector;

int solve(int n, vector<int> values, vector<int> weights, int m) {
    vector<int> memo1(m + 1, 0), memo2(m + 1, 0);
    for (int i = 0; i <= n; i++) {
        std::swap(memo1, memo2);

        for (int j = 0; j <= m; j++) {
            memo2[j] = memo1[j];

            if (j - weights[i - 1] >= 0) {
                memo2[j] = std::max(memo2[j], memo1[j - weights[i - 1]] + values[i - 1]);
            }
        }
    }

    int result = 0;
    for (int i = m; i >= 0; i--) {
        if (memo2[i] != 0) {
            result = memo2[i];
            break;
        }
    }

    return result;
}

int main() {
    std::string path;
    vector<std::filesystem::path> array_path;

    auto it = std::filesystem::directory_iterator(path);
    std::copy_if(
        std::filesystem::begin(it),
        std::filesystem::end(it),
        std::back_inserter(array_path),
        [](const auto& entry) {});

    for (auto& p : array_path) {
        std::ifstream fin(p.string());

        std::cout << p.string() << std::endl;

        int n, m;
        fin >> n >> m;

        vector<int> values, weights;
        for (int i = 0; i < n; i++) {
            int value, weight;
            fin >> value >> weight;

            values.push_back(value);
            weights.push_back(weight);
        }

        std::cout << solve(n, values, weights, m) << std::endl;
    }

    return 0;
}