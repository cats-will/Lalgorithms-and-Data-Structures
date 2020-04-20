#include <vector>
#include <string>
#include <fstream>
using namespace std;

const long long MOD = 1000000411;

struct myMap {
    vector<vector<pair<string, string> > > map;
    int mod = 1000029;

    myMap() {
        map.resize(mod);
    }

    int hash(string x) {
        long long hash = 0;
        for (int i = 0; i < x.size(); i++) {
            hash *= 53; 
            hash += x[i] - 'a' + 1;
            hash = (hash + MOD) % MOD;
        }
        hash %= mod;
        return hash;
    }

    void add(string x, string y) {
        int d = hash(x);
        for (auto& h : map[d]) {
            if (x == h.first) {
                h.second = y;
                return;
            }
        }
        map[d].push_back(make_pair(x, y));
    }

    void del(string x) {
        int d = hash(x);
        for (int i = 0; i < map[d].size(); i++) {
            if (map[d][i].first == x) {
                swap(map[d][i], map[d][map[d].size() - 1]);
                map[d].pop_back();
                return;
            }
        }
        return;
    }

    string get(string x) {
        int d = hash(x);
        for (auto y : map[d]) {
            if (y.first == x) {
                return y.second;
            }
        }
        return "none";
    }
};

int main()
{
    ifstream fin("map.in");
    ofstream fout("map.out");

    myMap o;
    string s;

    while (fin >> s) {
        string x;
        fin >> x;
        if (s == "put") {
            string y;
            fin >> y;
            o.add(x, y);
        } else if (s == "delete") {
            o.del(x);
        } else if (s == "get") {
            fout << o.get(x) << endl;
        }
    }
}

