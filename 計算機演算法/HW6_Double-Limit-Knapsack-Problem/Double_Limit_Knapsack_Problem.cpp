#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int volume;
    int val; //value
};

int W, V, n; //max weight, max volume, number of items
int maxVal = 0; //record current max value
vector<Item> items;
vector<int> valLeft; //total values of remaining item

void dfs(int index, int curW, int curV, int curVal) {
    if (curW > W || curV > V) return; //exceed weight or volume limit
    if (index == n) {
        if (curVal > maxVal) maxVal = curVal; //if all items considered, update max value
        return;
    }

    // pruning if remaining items cannot exceed current max value
    if (curVal + valLeft[index] <= maxVal) return;

    //recursion without selecting current item
    dfs(index + 1, curW, curV, curVal);

    //recursion with selecting current item if it doesn't exceed limits
    dfs(index + 1, curW + items[index].weight, curV + items[index].volume, curVal + items[index].val);
}

bool compareByValue(const Item &a, const Item &b) {
    return a.val > b.val;
}

int main() {
    ios::sync_with_stdio(false); //cancel synchronize with stdio
    cin.tie(nullptr); //untie cin and cout

    cin >> W >> V >> n;
    items.resize(n);
    
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].volume >> items[i].val;
    }

    //sort items by value in descending order
    sort(items.begin(), items.end(), compareByValue);

    valLeft.resize(n + 1); //last space for boundary
    valLeft[n] = 0; //no items left, no value

    //calculate total value of remaining items
    for (int i = n - 1; i >= 0; i--) {
        valLeft[i] = valLeft[i + 1] + items[i].val;
    }

    dfs(0, 0, 0, 0); //start DFS from the first item

    cout << maxVal << endl;

    return 0;
}
