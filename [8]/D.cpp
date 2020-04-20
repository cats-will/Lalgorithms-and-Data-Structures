#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void DFS(vector<vector<int>>& Graph,
         vector<int>& components,
         vector<bool>& visited,
         int v, int CNum) {
    visited[v] = true;
    components[v] = CNum;
    for (int i : Graph[v]) {
        if (!visited[i]) {
            DFS(Graph, components, visited, i, CNum);
        }
    }
}

int main() {

    ifstream fin("components.in");
    ofstream fout("components.out");

    int CNum = 0;
    int n, m;
    fin >> n >> m;

    vector<vector<int>> Graph(n, vector<int>());
    vector<int> components(n);
    vector<bool> visited(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        x--;
        y--;
        Graph[x].push_back(y);
        Graph[y].push_back(x);
    }

    for (int i = 0; i < Graph.size(); i++)
        if (!visited[i]) {
            CNum++;
            DFS(Graph, components, visited, i, CNum);
        }
    fout << CNum << endl;

    for (int component : components) {
        fout << component << " ";
    }

    fin.close();
    fout.close();
}
