#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <stack>

using namespace std;
using namespace std::chrono;

void quickSort(vector<int>& arr) {
    if (arr.empty()) return;
    stack<pair<int, int>> s;
    s.push({0, (int)arr.size() - 1});
    
    while (!s.empty()) {
        int low = s.top().first;
        int high = s.top().second;
        s.pop();
        
        if (low >= high)
            continue;

        int randomIndex = low + rand() % (high - low + 1);
        swap(arr[randomIndex], arr[high]);
        
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        if (low < pi - 1)
            s.push({low, pi - 1});
        if (pi + 1 < high)
            s.push({pi + 1, high});
    }
}

int main() {
    srand(time(NULL));

    ifstream file("data.csv");
    if (!file) {
        cout << "unable to open data.csv" << endl;
        return 1;
    }
    
    string line;
    vector<vector<int>> testData;

    while(getline(file, line)) {
        vector<int> numbers;
        stringstream ss(line);
        string value;
        
        while(getline(ss, value, ',')) {
            numbers.push_back(stoi(value));
        }
        if(!numbers.empty()){
            testData.push_back(numbers);
        }
    }
    
    file.close();
    
    int testCaseNumber = 1;
    long long total_time;
    for(auto &data : testData) {
        total_time = 0;
        cout << "Test Case " << testCaseNumber << ": include " << data.size() << " data" << endl;
        vector<int> sortedData;
        for (int c=0; c<50; c++) {
            vector<int> tempData = data;
            auto start = high_resolution_clock::now();
                quickSort(tempData);
            auto end = high_resolution_clock::now();
            auto durationStd = duration_cast<nanoseconds>(end - start);
            total_time += durationStd.count();
            sortedData = tempData;
        }
        cout << "QuickSort cost time: " << total_time/50 << " ns" << endl;

        cout << "10 data after sort: ";
        for (int i = 0; i<min((int)sortedData.size(), 10); i++) {
            cout << sortedData[i] << " ";
        }
        cout << "\n\n";
        testCaseNumber++;
    }
    return 0;
}
