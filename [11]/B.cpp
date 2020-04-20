#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
const int INF = 999999999;

void floyd(vector<vector<int>>& Graph, int n) {
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                Graph[i][j] = min(Graph[i][j], Graph[i][k] + Graph[k][j]);
}

int main() {

    ifstream fin ("pathsg.in");
    ofstream fout ("pathsg.out");

    int n, m;
    fin >> n >> m;
    vector<vector<int>> Graph;
    Graph.assign(n, vector <int>(n, INF));

    for(int i = 0; i < m; i++) {
        int x, y, weight;
        fin >> x >> y >> weight;
        Graph[x - 1][y - 1] = weight;
    }
    floyd(Graph, n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == j) {
                Graph[i][j] = 0;
            }
            fout << Graph[i][j] << ' ';
        }
        fout << endl;
    }
    fin.close();
    fout.close();
}