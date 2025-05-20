#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

int main() {
    ios::sync_with_stdio(false); //cancel synchronize with stdio
    cin.tie(nullptr); //untie cin and cout

    int C, n; //capacity, number of item types
    cin >> C >> n;

    vector<Item> items;

    // input items information
    for (int i = 0; i < n; ++i) {
        int w, v, k; //weight, value, max choosable number of item
        cin >> w >> v >> k;

        // binary split to only 1 choosable item (same as 01 knapsack problem)
        for (int j = 1; k > 0; j *= 2) {
            int count = min(j, k); //split to how many items
            items.push_back({w * count, v * count}); //items after split
            k -= count;
        }
    }

    // dp[i] means max value of capacity i
    vector<int> dp(C + 1, 0);

    // 01 knapsack dp
    for (int i = 0; i < items.size(); i++) {
        int w = items[i].weight;
        int v = items[i].value;
        for (int j = C; j >= w; j--) {
            if (dp[j - w] + v > dp[j]) {
                dp[j] = dp[j - w] + v;
            }
        }
    }

    cout << dp[C] << endl;

    return 0;
}
