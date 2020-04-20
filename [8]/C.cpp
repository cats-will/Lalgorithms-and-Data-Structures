//
// Created by Catswill on 25.02.2020.
//
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    bool p = true;
    int k = 0;
    int i = 0;

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;
    int v[m], g[m];

    for (int i = 0; i < m; ++i){
        fin >> v[i] >> g[i];
    }

    while (p){
        for (int j = i + 1; j < m; ++j){
            if ((v[i] == g[j] && g[i] == v[j]) || (v[i] == v[j] && g[i] == g[j])){
                k++;
                p = false;
            }
        }
        i++;
        if (i == m){
            break;
        }
    }
    if (k == 0){
        fout << "NO" << endl;
    }
    else {
        fout << "YES" << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
