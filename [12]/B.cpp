#include <fstream>
#include <vector>
#include <queue>
 
using namespace std;
 
const int INF = 1e9 + 7;
 
struct edge {
    int c;
    int flow;
    int from;
    int to;
};
 
void add_edge(vector<edge> &e, vector<vector<int>> &G, int from, int to, int c) {
    G[from].push_back(e.size());
    e.push_back({c, 0, from, to});
    G[to].push_back(e.size());
    e.push_back({0, 0, to, from});
}
 
bool BFS(const vector<vector<int>> &G, vector<edge> &e, vector<int> &dist,
 int s, int t) {
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
 
int
DFS(const vector<vector<int>> &G, vector<edge> &e, vector<int> &dist, vector<int> &p, int s, int t, int flow = INF) {
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
 
int Dinic(vector<vector<int> > &G, vector<edge> &e, int s, int t) {
    int flow = 0;
    vector<int> dist;
    while (BFS(G, e, dist, s, t)) {
        vector<int> p(G.size(), 0);
        for (;;) {
            int f = DFS(G, e, dist, p, s, t);
            if (f == 0) {
                break;
            } else {
                flow += f;
            }
        }
    }
    return flow;
}
 
int main() {
  ifstream fin("matching.in");
  ofstream fout("matching.out");
    
  int n, m, k;
  fin >> n >> m >> k;
  vector<vector<int> > G(n + m + 2);
  vector<edge> e;
  for (int i = 0; i < k; ++i) {
    int from, to;
    fin >> from >> to;
    add_edge(e, G, from, to + n, 1);
  } 
  for(int i = 1; i <= n; ++i) { 
    add_edge(e, G, 0, i, 1);
  }
  for(int j = 1; j <= m; ++j) {
    add_edge(e, G, n + j, n + m + 1, 1); 
  }
  fout << Dinic(G, e, 0, m + n + 1) << endl;
}

