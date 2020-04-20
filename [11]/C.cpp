#include <fstream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 3;

vector<ll> dijkstra(const vector<vector<pair<int, ll>>> &Graph, int s) {
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
    return dist;
}

int main() {

    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");

    int n, m;
    fin >> n >> m;
    vector<vector<pair<int,ll>>> Graph(n);

    for(int i = 0; i < m; i++) {
        int x, y;
        ll weight;
        fin >> x >> y >> weight;
        Graph[--x].push_back({y, weight});
        Graph[--y].push_back({x, weight});
    }
    vector<ll> dist = dijkstra(Graph, 0);

    for(ll d : dist) {
        fout << d << " ";
    }

    fin.close();
    fout.close();
}