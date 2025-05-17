#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N; //City number
    cin >> N;

    // N*N matrix, distance from city i to city j
    vector<vector<int>> distance(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> distance[i][j];
        }
    }
    
    // Precompute reachable cities
    vector<vector<int>> neighbors(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(distance[i][j] != -1 && i != j) {
                neighbors[i].push_back(j);
            }
        }
    }

    const int INF = 1e9; //Unreachable
    int totalStates = 1 << N; //All cities visit state
    
    vector<vector<int>> dp(totalStates, vector<int>(N, INF)); //Record shortest path
    vector<vector<int>> previous(totalStates, vector<int>(N, -1)); //Record previous path
    
    dp[1 << 0][0] = 0; //Start from city 0
    
    // Visit all cities
    for (int state = 0; state < totalStates; state++) {
        for (int i = 0; i < N; i++) {
            if(dp[state][i] == INF) continue; //City i unreachable

            // Visit all cities j from city i
            for (int j : neighbors[i]) {
                if(state & (1 << j)) continue; //City j has visited

                int nextState = state | (1 << j); //Set j as visited
                
                // Update shortest path
                if(dp[state][i] + distance[i][j] < dp[nextState][j]) {
                    dp[nextState][j] = dp[state][i] + distance[i][j];
                    previous[nextState][j] = i;
                }
            }
        }
    }
    
    // Find best path return to starting city
    int minDistance = INF, lastCity = -1, fullState = totalStates - 1;
    for (int i = 0; i < N; i++) {
        if(dp[fullState][i] < INF && distance[i][0] != -1) { //All cities visited and path from i to Starting city exists
            if(dp[fullState][i] + distance[i][0] < minDistance){
                minDistance = dp[fullState][i] + distance[i][0];
                lastCity = i;
            }
        }
    }
    
    // No valid path to starting city
    if(lastCity == -1) {
        cout << -1 << endl;
        return 0;
    }
    
    //Reconstruct path
    vector<int> path;
    int currentCity = lastCity;
    int currentState = fullState;
    while(currentCity != -1) {
        path.push_back(currentCity);
        int prevCity = previous[currentState][currentCity];
        currentState = currentState & ~(1 << currentCity); //Remove current city from state
        currentCity = prevCity;
    }

    reverse(path.begin(), path.end()); //Reverse path to correct order
    path.push_back(0); //Add starting city to end of path
    
    // Output path 
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] + 1;
        if(i != path.size() - 1)
            cout << " ";
    }

    return 0;
}
