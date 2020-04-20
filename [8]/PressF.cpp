#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const char way[4] = {'D', 'U', 'R', 'L'};

void BFS(int x, int y,
         const vector<vector<int>> &labirint,
         vector<vector<int>> &dist,
         vector<vector<char>> &pred) {
    queue<pair<int, int> > q;
    q.push({x, y});
    int n = labirint.size();
    int m = labirint[0].size();
    dist[x][y] = 0;
    while(!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int cx = x + dx[i];
            int cy = y + dy[i];
            if (cx >= 0 && cy >= 0 && cx < n && cy < m && labirint[cx][cy] == 1 && dist[cx][cy] == -1) {
                dist[cx][cy] = dist[x][y] + 1;
                pred[cx][cy] = way[i];
                q.push({cx, cy});
            }
        }
    }
}

int main() {

    ifstream fin ("input.txt");
    ofstream fout ("output.txt");

    int n, m;
    fin >> n >> m;
    vector<vector<int>> labirint(n, vector<int>());

    int x1, x2, y1, y2;
    for(int i = 0; i < n; i++ ) {
        for (int j = 0; j < m; j++) {
            char x;
            fin >> x;
            switch(x) {
                case '.':
                    labirint[i].push_back(1);
                    break;
                case '#':
                    labirint[i].push_back(0);
                    break;
                case 'S':
                    labirint[i].push_back(1);
                    x1 = i;
                    y1 = j;
                    break;
                case 'T':
                    labirint[i].push_back(1);
                    x2 = i;
                    y2 = j;
                    break;
                default:break;
            }
        }
    }
    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<char>> pred(n, vector<char>(m, '.'));

    BFS(x1, y1, labirint, dist, pred);
    fout << dist[x2][y2] << endl;
    if(dist[x2][y2] != -1){
        string path;
        for (int i = x2, j = y2; i != x1 || j != y1;) {
            path.push_back(pred[i][j]);
            switch(pred[i][j]) {
                case 'U':
                    i++;
                    break;
                case 'D':
                    i--;
                    break;
                case 'L':
                    j++;
                    break;
                case 'R':
                    j--;
                    break;
                default:break;
            }
        }
        reverse(path.begin(), path.end());
        fout << path << endl;
    }
    fin.close();
    fout.close();
}

