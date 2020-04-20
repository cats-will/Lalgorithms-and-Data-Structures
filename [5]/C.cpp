#include <fstream>
#include <vector>
#include <string>
using namespace std;

const long long MOD = 1000000123;

struct node {
    string x, y;
    node *prev, *next;

    node (string x_ = "", string y_ = "", node *prev_ = NULL, node *next_ = NULL) {
        x = x_;
        y = y_;
        next = next_;
        prev = prev_;
    }

    void del() {
      x = "";
      y = "";
      next = NULL;
      prev = NULL;
    }
};

struct myMap {
    vector<vector<node *> > map;
    node *last = NULL;
    int mod = 1000027;

    myMap() {
        map.resize(mod);
    }

    int hash(string& x) {
        long long hash = 0;
        for (int i = 0; i < x.size(); i++) {
            hash *= 123;
            hash += (MOD + x[i] - 'A' + 1);
            hash %= MOD;
        }
        return hash % mod;
    }

    void add(string x, string y) {
        int h = hash(x);
        for (auto p : map[h]) {
            if (p -> x == x) {
                p -> y = y;
                return;
            }
        }
        map[h].push_back(new node(x, y));
        push(map[h].back());
    }

    void push(node *x) {
        if (last == NULL) {
            last = x;
            return;
        }
        x -> prev = last;
        last -> next = x;
        last = x;
    }

    void del(string x) {
        int h = hash(x);
        for (int i = 0; i < map[h].size(); i++) {
            if (map[h][i] -> x == x) {
                pop(map[h][i]);
                swap(map[h][i], map[h].back());
                map[h].pop_back();
                return;
            }
        }
    }

    void pop(node *x) {
        if (!x -> next) {
            last = x -> prev;
            if (last) last -> next = NULL;
        } else {
            x -> next -> prev = x -> prev;
            if (x -> prev) x -> prev -> next = x -> next;
        }
        x -> del();
    }

    string get(string x) {
        int h = hash(x);
        for (auto p : map[h]) {
            if (p -> x == x) {
                return p -> y;
            }
        }
        return "none";
    }

    string prev(string x) {
        int h = hash(x);
        for (auto p : map[h]) {
            if (p -> x == x) {
                if (p -> prev) {
                    return p -> prev -> y;
                } else {
                    return "none";
                }
            }
        }
        return "none";
    }

    string next(string x) {
        int h = hash(x);
        for (auto p : map[h]) {
            if (p -> x == x) {
                if (p -> next) {
                    return p -> next -> y;
                } else {
                    return "none";
                }
            }
        }
        return "none";
    }
};

int main()
{
    ifstream fin("linkedmap.in");
    ofstream fout("linkedmap.out");

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
        } else if (s == "prev") {
            fout << o.prev(x) << endl;
        } else if (s == "next") {
            fout << o.next(x) << endl;
        }
    }
}