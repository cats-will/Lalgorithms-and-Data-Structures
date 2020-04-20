#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool bipartiteGraph(int v, const vector<vector<int>>& Graph, vector<int>& state, int color) {
    state[v] = color;
    for(int i  = 0; i < Graph[v].size(); i++) {
        int u = Graph[v][i];
        if(state[u] == color) {
            return false;
        }
        else if (state[u] == 0) {
            if(!bipartiteGraph(u, Graph, state, color == 1 ? 2 : 1)) {
                return false;
            }
        }
    }
    return true;
}

int main() {

    ifstream fin("bipartite.in");
    ofstream fout("bipartite.out");

    int n, m;
    fin >> n >> m;
    vector<vector<int> > Graph(n);
    vector<int> state(n);

    for(int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        Graph[x - 1].push_back(y - 1);
        Graph[y - 1].push_back(x - 1);
    }

    bool result = true;
    for(int i = 0; i < n; i++) {
        if(state[i] == 0) {
            result &= bipartiteGraph(i, Graph, state, 1);
        }
    }
    fout << (result == true ? "YES" : "NO");

    fin.close();
    fout.close();
}