#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    int x, y;
    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        matrix[x - 1][y - 1] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fout << matrix[i][j] << " ";
        }
        fout << endl;
    }

    fin.close();
    fout.close();
}