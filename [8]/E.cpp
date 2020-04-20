#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int main() {

    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");

    int n, m;
    fin >> n >> m;
    vector<vector<int>> graph(n, vector<int>());

    vector<bool> used(n);
    used[0] = true;

    vector<int> path(n);
    path[0] = 0;

    queue<int> q;
    q.push (0);

    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        x--;
        y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : graph[v]) {
            if (!used[to]) {
                q.push(to);
                used[to] = true;
                path[to] = path[v] + 1;
            }
        }
    }
    
    for (int i = 0; i < n; i++){
        fout  << path[i] << " ";
    }

    fin.close();
    fout.close();
}
