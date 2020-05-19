#include <fstream>
#include <vector>
#include <string>
 
using namespace std;
 
vector<int> KMP(const string& s, int pattern_len) {
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
  vector<int> answer;
  for(int i = 0; i < p.size(); i++)
    if(p[i]==pattern_len)
      answer.push_back(i-2*pattern_len+1);
  return answer;
}

int main() {

  ifstream fin("search2.in");
  ofstream fout("search2.out");

  string p, t;
  fin >> p >> t;

  vector<int> pi(p.length());

  vector<int> ans = KMP(p+"#"+t, p.length());
  fout << ans.size() << '\n';
  for(auto i : ans) {
    fout << i << " ";
  }
}