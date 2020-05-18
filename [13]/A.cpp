#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> NaiveStringMatcher(string p, string t, vector<int>& ans) {
    int n = t.length();
    int m = p.length();
    for(int i = 0; i <= n - m; ++i) {
        bool correct = true;
        for(int j = 0; j < m; j++) {
            if(p[j] != t[i + j])
                correct = false;
        }
        if(correct)
            ans.push_back(i + 1);
    }
    return ans;
}

int main() {
    ifstream fin("search1.in");
    ofstream fout("search1.out");

    vector<int> ans;
    string p, t;
    fin >> p >> t;

    NaiveStringMatcher(p, t, ans);

    fout << ans.size() << endl;
    for(auto a : ans) {
        fout << a << " ";
    }
} 