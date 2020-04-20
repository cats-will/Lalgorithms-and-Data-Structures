#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define white 0
#define gray 1
#define black 2
using namespace std;

bool DFS(int v, const vector<vector<int>> &Graph, vector<int> &state, vector<int> &cycle) {
    state[v] = gray;
    for (int i = 0; i < Graph[v].size(); i++) {
        int u = Graph[v][i];
        if(state[u] == white) {
            if (DFS(u, Graph, state, cycle)) {
                state[v] = black;
                cycle.push_back(v);
                return true;
            }
        }
        else if(state[u] == gray) {
            state[v] = black;
            cycle.push_back(u);
            cycle.push_back(v);
            return true;
        }
    }
    state[v] = black;
    cycle.clear();
    return false;
}

vector<int> GetCycle(const vector<vector<int>>& Graph) {
    vector<int> state(Graph.size(), white);
    for (int i = 0; i < Graph.size(); i++) {
        if (state[i] == white) {
            vector<int> cycle;
            if(DFS(i, Graph, state, cycle)) {
                while (cycle.back() != cycle[0]) {
                    cycle.pop_back();
                }
                reverse(cycle.begin(), cycle.end());
                cycle.erase(cycle.begin());
                return cycle;
            }
        }
    }
    return vector<int>(0);
}

int main() {

    ifstream fin("cycle.in");
    ofstream fout("cycle.out");

    int n, m;
    fin >> n >> m;
    vector<vector<int> > Graph(n, vector<int>(0));

    for(int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        Graph[x - 1].push_back(y - 1);
    }
    vector<int> cycle = GetCycle(Graph);
    
    if (cycle.empty()) {
        fout << "NO" << endl;
    }
    else {
        fout << "YES" << endl;
        for (int i : cycle) {
            fout << i + 1 << " ";
        }
    }
    fin.close();
    fout.close();
}