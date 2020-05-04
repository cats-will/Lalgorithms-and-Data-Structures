#include <vector>
#include <queue>
#include <fstream>
  
using namespace std;
  
const int INF = 1e9 + 7;

ifstream fin("circulation.in");
ofstream fout("circulation.out");
  
struct edge {
    int c;
    int flow;
    int from;
    int to;
    int reverse;
};
  
void add_edge(vector<edge> &e, vector<vector<int>> &G, int from, int to, int c, int reverse = -1) {
    G[from].push_back(e.size());
    e.push_back({c, 0, from, to, reverse});
    G[to].push_back(e.size());
    e.push_back({0, 0, to, from, reverse});
}
  
void add_more(vector<edge> &e, vector<vector<int>> &G, int from, int to, int min_flow, int max_flow){
    add_edge(e, G, from, to, max_flow - min_flow);
    add_edge(e, G, G.size() - 2, to, min_flow, e.size() - 2);
    add_edge(e, G, from, G.size() - 1, min_flow);
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
  
void Dinic(vector<vector<int>> &G, vector<edge> &e, int s, int t) {
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
    vector<int> answer;
    for(auto i : G[s]) {
        if(e[i].flow == e[i].c)
            answer.push_back(e[i].flow + e[e[i].reverse].flow);
        else {
            fout << "NO\n";
            return;
        }
    }
    fout << "YES\n";
    for(auto i : answer)
        fout << i << endl;
}
  
int main() {
    int n, m;
    fin >> n >> m;
    vector<vector<int>> G(n+2);
    vector <edge> e;
    for (int i = 0; i < m; ++i) {
        int from, to, min_flow, max_flow;
        fin >> from >> to >> min_flow >> max_flow;
        --from;
        --to;
        add_more(e, G, from, to, min_flow, max_flow);
    }
    Dinic(G, e, G.size()-2, G.size()-1);
}
