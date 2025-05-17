#include <bits/stdc++.h>

using namespace std;

int W, n; //Target weight, number of objects
vector<int> w; //Object weights
vector<long long> ans;

void dfs(int i, long long curr_sum, long long mask) {
    if (curr_sum > W) return; //prune branches
    if (i == n) {
        if (curr_sum == W) ans.push_back(mask);
        return;
    }
    dfs(i + 1, curr_sum, mask); //not choose current object
    dfs(i + 1, curr_sum + w[i], mask | (1LL << (n - 1 - i)));
}

int main() {
    // Speed up I/O
    ios::sync_with_stdio(false); //Cancel synchronization between C & C++ standard streams
    cin.tie(nullptr); //Untie cin and cout

    string line;
    if (!getline(cin, line)) return 0; //Read input line
    stringstream ss(line);
    vector<long long> v;
    long long x;
    while (ss >> x) v.push_back(x); //Read integers from line into vector v

    if (v.empty()) return 0;
    W = v[0]; //Target weight
    n = (int)v.size() - 1; //Number of objects
    w.assign(n, 0);
    for (int i = 0; i < n; i++) w[i] = v[i + 1]; //store object weights

    dfs(0, 0, 0);

    sort(ans.begin(), ans.end()); //Sort results in ascending order
    bool first = true;
    for (auto m : ans) { //Print results
        if (!first) cout << ' ';
        first = false;
        cout << m;
    }
    cout << "\n";
    
    return 0;
}
