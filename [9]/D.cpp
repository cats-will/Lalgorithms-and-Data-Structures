#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define white 0
#define black 1

using namespace std;

void DFS(int v, const vector<vector<int> >& Graph, vector<int>& state, vector<int>& result) {
    state[v] = black;
    for (int i = 0; i < Graph[v].size(); i++) {
        int u = Graph[v][i];
        if(state[u] == white) {
            DFS(u, Graph, state, result);
         }
    }
    result.push_back(v);
}

void top_sort(const vector<vector<int> >& Graph, vector<int>& result) {
    vector<int> state (Graph.size(), white);
    for(int i = 0; i < Graph.size(); i++) {
        if(state[i] == white) {
             DFS(i, Graph, state, result);
        }
    }
    reverse(result.begin(), result.end());
}

void DFS2(int v, const vector<vector<int>>& Graph, vector<int>& state, int color) {
    state[v] = color;
    for(auto u : Graph[v]) {
        if(state[u] == 0) {
            DFS2(u, Graph, state, color);
        }
    }
}

int Cond(const vector<vector<int>>& Graph, const vector<vector<int>>& GraphT, vector<int>& state) {
    vector<int> result(Graph.size());
    top_sort(Graph, result);
    int color = 0;
    for(auto u : result) {
        if(state[u] == 0) {
            color++;
            DFS2(u, GraphT, state, color);
        }
    }
    return color;
}

int main() {

    ifstream fin("cond.in");
    ofstream fout("cond.out");

    int n, m;
    fin >> n >> m;

    vector<vector<int> > Graph(n);
    vector<vector<int> > GraphT(n);
    vector<int> state(n);

    for(int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        Graph[x - 1].push_back(y - 1);
        GraphT[y - 1].push_back(x - 1);
    }

    int count = Cond(Graph, GraphT, state);
    fout << count << endl;
    for(auto i : state) {
        fout << i << " ";
    }
}