#include <fstream>
#include <vector>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 3;

ll dijkstra(const vector<vector<pair<int, ll>>> &Graph, int s, int f) {
    int n = Graph.size();
    vector <ll> dist(n, INF);
    dist[s] = 0;
    set<pair<ll, int> > q;
    q.insert(make_pair(0, s));
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto i : Graph[v]) {
            int v2 = i.first;
            if (i.second + dist[v] < dist[v2]) {
                q.erase(make_pair(dist[v2], v2));
                dist[v2] = i.second + dist[v];
                q.insert(make_pair(dist[v2], v2));
            }
        }
    }
    return dist[f] != INF ? dist[f] : -1;
}

int main() {

    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");

    int n, s, f;
    fin >> n >> s >> f;
    --s;
    --f;
    vector<vector<pair<int,ll>>> Graph(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ll weight;
            fin >> weight;
            if (weight == -1 || i == j)
                continue;
            Graph[i].emplace_back(j, weight);
        }
    }
    fout << dijkstra(Graph, s, f);
}