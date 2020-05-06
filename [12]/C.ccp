#include <fstream>
#include <vector>
#include <queue>
 
using namespace std;
 
const int INF = 1e9 + 7;
 
ifstream fin("decomposition.in");
ofstream fout("decomposition.out");
 
struct edge {
    int c;
    int flow;
    int from;
    int to;
    int number;
};
 
void add_edge(vector<edge> &e, vector<vector<int>> &G, int from, int to, int c, int number) {
    G[from].push_back(e.size());
    e.push_back({c, 0, from, to, number});
    G[to].push_back(e.size());
    e.push_back({0, 0, to, from, number});
}
 
bool BFS(const vector<vector<int>> &G, vector<edge> &e, vector<int> &dist, int s, int t) {
    queue<int> q;
    dist.assign(G.size(), -1);
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto i : G[v]) {
            if (e[i].flow < e[i].c && dist[e[i].to] == -1) {
                dist[e[i].to] = dist[v] + 1;
                q.push(e[i].to);
            }
        }
    }
    return dist[t] != -1;
}
 
int DFS(const vector<vector<int>> &G, vector<edge> &e, vector<int> &dist, vector<int> &p, int s, int t, int flow = INF) {
    if (flow == 0 || s == t) {
        return flow;
    }
    for (; p[s] < G[s].size(); p[s]++) {
        int i = G[s][p[s]];
        if (dist[s] + 1 == dist[e[i].to]) {
            int to = e[i].to;
            int f = DFS(G, e, dist, p, to, t, min(flow, e[i].c - e[i].flow));
            if (f != 0) {
                e[i].flow += f;
                e[i ^ 1].flow -= f;
                return f;
            }
        }
    }
    return 0;
}
 
long long DFS2(const vector<vector<int>>&G, vector<edge>&e, vector<vector<int>> &path, int to, int flow){
    if(to == G.size() - 1)
        return flow;
    for(auto &i : G[to]) {
        if(e[i].flow > 0) {
            long long path_flow = DFS2(G, e, path, e[i].to, min(flow, e[i].flow));
            if (path_flow > 0) {
                path.back().push_back(e[i].number);
                e[i].flow -= path_flow;
                return path_flow;
            }
        }
    }
    return 0;
}
 
void Dinic(const vector<vector<int>> &G, vector<edge> &e, int s, int t) {
    int flow = 0;
    vector<int> dist;
    vector<vector<int>> paths;
    while (BFS(G, e, dist, s, t)) {
        vector<int> p(G.size(), 0);
        while(int f = DFS(G, e, dist, p, s, t)){};
    }
    paths.emplace_back();
    vector<int> flows;
    while(int flow = DFS2(G, e, paths, s, INF)) {
        flows.push_back(flow);
        paths.emplace_back();
    }
    fout << paths.size() - 1 << endl;
    for(int i = 0; i < paths.size() - 1; i++) {
        fout << flows[i] << " " << paths[i].size() << " ";
        for(int j = paths[i].size() - 1; j >= 0; j--)
            fout << paths[i][j] << " ";
        fout << endl;
    }
}
 
int main() {
    int n, m;
    fin >> n >> m;
    vector<vector<int>> G(n);
    vector<edge> e;
    for (int i = 0; i < m; ++i) {
        int from, to, c;
        fin >> from >> to >> c;
        --from;
        --to;
        add_edge(e, G, from, to, c, i+1);
    }
    Dinic(G, e, 0, n - 1);
}
