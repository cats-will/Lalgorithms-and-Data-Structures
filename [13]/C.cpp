#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> Prefix(const string& s) {
  int m = s.length();
  vector<int> p(m);
  for(int i = 1; i < m; i++) {
    int k = p[i - 1];
    while(k > 0 && s[i] != s[k]) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      k++;
    }
    p[i] = k;
  }
  return p;
}

int main() {
  ifstream fin("prefix.in ");
  ofstream fout("prefix.out");

  string s;
  fin >> s;

  vector<int> ans = Prefix(s);
  for(auto a : ans) {
    fout << a << " ";
  }
} 