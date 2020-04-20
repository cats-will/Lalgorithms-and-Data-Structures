#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define white 0
#define gray 1
#define black 2
using namespace std;

bool DFS(int v, const vector<vector<int>> &Graph, vector<int> &state, vector<int> &result) {
    state[v] = gray;
    for (int i = 0; i < Graph[v].size(); i++) {
        int u = Graph[v][i];
        if(state[u] == white) {
            if (DFS(u, Graph, state, result))
                return true;
        }
        else if(state[u] == gray) {
            return true;
        }
    }
    state[v] = black;
    result.push_back(v + 1);
    return false;
}

void top_sort(const vector<vector<int>> &Graph, vector<int> &result) {
    vector<int> state (Graph.size(), white);
    for(int i = 0; i < Graph.size(); i++) {
        if(state[i] == white) {
            bool cycle = DFS(i, Graph, state, result);
            if(cycle) {
                result.clear();
                result.push_back(-1);
                return;
            }
        }
    }
    reverse(result.begin(), result.end());
}

int main() {

    ifstream fin("topsort.in");
    ofstream fout("topsort.out");

    int n, m;
    fin >> n >> m;
    vector<vector<int> > Graph(n);
    vector<int> result;

    for(int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        Graph[x - 1].push_back(y - 1);
    }
    top_sort(Graph, result);

    for(int i = 0; i < result.size(); i++) {
        fout << result[i] << " ";
    }

    fin.close();
    fout.close();
}