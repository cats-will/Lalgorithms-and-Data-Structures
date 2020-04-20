#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void DFS(int v, vector<bool>& used, vector<int>& result, const vector<vector<int>>& Graph) {
    used[v] = true;
    for(auto u : Graph[v]) {
        if(!used[u]) {
            DFS(u, used, result, Graph);
        }
    }
    result.push_back(v);
}
int main() {

    ifstream fin("hamiltonian.in");
    ofstream fout("hamiltonian.out");

    int n, m;
    fin >> n >> m;
    vector<bool> used(n, false);
    vector<vector<int>> Graph(n);
    vector<int> result;

    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        Graph[x - 1].push_back(y - 1);
    }
    for(int i = 0; i < n; i++) {
        if(!used[i]) {
            DFS(i, used, result, Graph);
        }
    }
    int count = 0;
    for(int i = result.size() - 1; i > 0; i--) {
        for(auto u : Graph[result[i]]) {
            if(u == result[i - 1]) {
                count++;
                break;
            }
        }
    }
    fout << ((count == result.size() - 1) ? "YES" : "NO");
    fin.close();
    fout.close();
}