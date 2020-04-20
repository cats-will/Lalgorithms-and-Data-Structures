#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void DFS(int v, const vector<vector<int>>& Graph, vector<int>& win) {
    for(int i = 0; i < Graph[v].size(); i++) {
        int u = Graph[v][i];
        if(win[u] == 0) {
            DFS(u, Graph, win);
        }
    }
    if(Graph[v].empty()) {
        win[v] = -1;
        return;
    }
    win[v] = -1;
    for(int u : Graph[v]) {
        if(win[u] == -1){
            win[v] = 1;
            return;
        }
    }
}

bool firstPlayerWin(const vector<vector<int>>& Graph, int start) {
    vector<int> win(Graph.size(), 0);
    DFS(start, Graph, win);
    return win[start] == 1;
}

int main () {
    ifstream fin("game.in");
    ofstream fout("game.out");

    int n, m, s;
    fin >> n >> m >> s;

    s--;
    vector<vector<int>> Graph(n);

    for(int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        Graph[x - 1].push_back(y - 1);
    }
    fout << (firstPlayerWin(Graph, s) ? "First player wins" : "Second player wins") << endl;

    fin.close();
    fout.close();
    return 0;
}













