#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct mySet {
    vector<vector<int>> set;
    int mod = 1000029;

    mySet() {
        set.resize(mod);
    }

    int hash(int x) {
        return abs(x) % mod;
    }

    void add(int x) {
        int d = hash(x);
        bool cool = false;
        for (int y : set[d]) {
            if (y == x) {
                cool = true;
            }
        }
        if (cool) return;
        set[d].push_back(x);
    }

    void del(int x) {
        int d = hash(x);
        for (int i = 0; i < set[d].size(); i++) {
            if (set[d][i] == x) {
                swap(set[d][i], set[d].back());
                set[d].pop_back();
                return;
            }
        }
        return;
    }

    bool exists(int x) {
        int d = hash(x);
        for (int y : set[d]) {
            if (y == x) {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    ifstream fin("set.in");
    ofstream fout("set.out");

    mySet o;
    string s;

    while (fin >> s) {
        int x;
        fin >> x;
        if (s == "insert") {
            o.add(x);
        } else if (s == "delete") {
            o.del(x);
        } else if (s == "exists") {
            if (o.exists(x)) {
                fout << "true\n";
            } else {
                fout << "false\n";
            }
        }
    }
}
