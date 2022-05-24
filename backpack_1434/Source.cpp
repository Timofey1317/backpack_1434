#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

int solve(int n, vector<int> values, vector<int> weights, int m) {
    vector<int> memo1(m + 1, 0);
    vector<int> memo2(m + 1, 0);
    for (int i = 0; i <= n; i++) {
        vector<int> temp = memo1;
        memo1 = memo2;
        memo2 = temp;
        for (int j = 0; j <= m; j++) {
            memo2[j] = memo1[j];
            if (j - weights[i - 1] >= 1) {
                memo2[j] = max(memo2[j], memo1[j - weights[i - 1]] + values[i - 1]);
            }
        }
    }
    int result;
    for (int i = m; i >= 0; i--) {
        if (memo2[i] != 0) {
            result = memo2[i];
            break;
        }
    }
    return result;
}

int main() {
    string path = "";
    auto it = filesystem::directory_iterator(path);
    vector<filesystem::path> array_path;
    copy_if(filesystem::begin(it), filesystem::end(it), std::back_inserter(array_path), [](const auto& entry) {
        });
    for (auto& p : array_path) {
        ifstream fin;
        fin.open(p.string());
        cout << p.string() << endl;
        int n, m;
        fin >> n >> m;
        vector<int> values;
        vector<int> weights;
        for (int i = 0; i < n; i++) {
            int value, weight;
            fin >> value >> weight;
            values.push_back(value);
            weights.push_back(weight);
        }
        int max_value = solve(n, values, weights, m);
        cout << max_value << endl;
    }
    return 0;
}